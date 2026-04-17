#include <iostream>
#include <numeric>
#include <cstring>

#include "yolo26.h"

int RKNNYOLO26Detection::loadModel(const char *modelPath) {
    rknn_core_mask core_mask = RKNN_NPU_CORE_0;
    int ret = RKNNModel::loadModel(modelPath, core_mask);

    // Set number of classes & number of boxes based on output attributes
    if (modelMetadata.io_num.n_output != 9) {
        std::cerr << "[WARNING] This RKNN model may not be compatible with the optimized YOLO26 detection pipeline.\n"
                  << "Expected 9 outputs, but got " << modelMetadata.io_num.n_output << ".\n"
                  << "Ask Ka Xuan for conversion guide\n";
    }

    numClasses_ = modelMetadata.output_attrs[1].dims[modelMetadata.output_attrs[0].n_dims - 3];

    const int default_branch = 3;
    const int pair_per_branch = modelMetadata.io_num.n_output / 3;

    numBoxes_ = 0;
    for (int b = 0; b < default_branch; ++b) {
        int box_idx = b * pair_per_branch;
        numBoxes_ += modelMetadata.output_attrs[box_idx].dims[2] * modelMetadata.output_attrs[box_idx].dims[3];
    }
    setOutputWantFloat(true);

    // input_mems = new rknn_tensor_mem[modelMetadata.io_num.n_input];
    for (int i = 0; i < modelMetadata.io_num.n_input; i++) {
        rknn_tensor_mem* mem = rknn_create_mem(modelMetadata.rknn_ctx, modelMetadata.input_attrs[i].size_with_stride);
        rknn_set_io_mem(modelMetadata.rknn_ctx, mem, &modelMetadata.input_attrs[i]);
        input_mems.push_back(mem);
    }

    // output_mems = new rknn_tensor_mem[modelMetadata.io_num.n_output];
    for (int i = 0; i < modelMetadata.io_num.n_output; i++) {
        rknn_tensor_mem* mem = rknn_create_mem(modelMetadata.rknn_ctx, modelMetadata.output_attrs[i].size_with_stride);
        rknn_set_io_mem(modelMetadata.rknn_ctx, mem, &modelMetadata.output_attrs[i]);
        output_mems.push_back(mem);
    }

    return ret;
}

int RKNNYOLO26Detection::process(const image_t& image, std::vector<RKNNResult>& results) 
{
    int ret = -1;

    if (image.width == 0 || image.height == 0) {
        fprintf(stderr, "Yolo26Detection::process :: Image area is 0\n");
        return ret;
    }
    
    // Ignore Preprocess for now
    image_t finalImage;
    finalImage.width = modelMetadata.model_width;
    finalImage.height = modelMetadata.model_height;
    // preprocess(image, finalImage);

    rknn_tensor_attr& attr = modelMetadata.input_attrs[0];

    int width = attr.dims[2];
    int height = attr.dims[1];
    int channel = attr.dims[3];
    int stride = attr.w_stride;

    std::cout << finalImage.width << " " << finalImage.height << " " << channel << std::endl;
    std::cout << width << " " << stride << std::endl;
    if (width == stride) {
        memcpy(input_mems[0]->virt_addr, image.data, attr.size);
    } else {
        uint8_t *src_ptr = (uint8_t *)image.data;
        uint8_t *dst_ptr = (uint8_t *)input_mems[0]->virt_addr;
        for (int h = 0; h < height; ++h) {
            memcpy(dst_ptr, src_ptr, width * channel);
            src_ptr += width * channel;
            dst_ptr += stride * channel;
        }
    }

    rknn_input inputs[modelMetadata.io_num.n_input];
    rknn_output outputs[modelMetadata.io_num.n_output];
    memset(inputs, 0, sizeof(inputs));
    memset(outputs, 0, sizeof(outputs));

    

    // Set input (assume single input)
    inputs[0].index = 0;
    inputs[0].type = RKNN_TENSOR_UINT8;  // Hardcode to UINT8 as other modules do
    inputs[0].fmt = modelMetadata.tensor_format;
    inputs[0].size = modelMetadata.model_height * modelMetadata.model_width * modelMetadata.model_channel;
    inputs[0].buf = finalImage.data;

    ret = infer(inputs, outputs);

    if (ret < 0)
    {
        std::cerr << "RKNNModule::infer failed :: " << get_error_message(ret) << std::endl;
    }
    else
    {
        // postprocess(image, outputs, results);
    }

    int r = releaseOutputs(outputs);
    if (r < 0)
    {
        std::cerr << "rknn_outputs_release failed :: " << get_error_message(r) << std::endl;
    }

    return ret;
}

void RKNNYOLO26Detection::preprocess(const image_t& img, image_t& out_img) 
{
    letterbox(
        img, out_img, 
        letterboxInfo, 
        640, 640, 128, 
        false, 32, false
    );
}

// void RKNNYOLO26Detection::postprocess(const cv::Mat& image, void* outputs, void* result_out)
// {
    
//     rknn_output* out = reinterpret_cast<rknn_output*>(outputs);
//     auto* results = static_cast<std::vector<RKNNResult>*>(result_out);

//     std::vector<std::vector<Detection>> output;

//     const int default_branch = 3;
//     const int pair_per_branch = modelMetadata.io_num.n_output / 3;

//     for (int b = 0; b < default_branch; ++b) {
//         int box_idx = b * pair_per_branch;
//         int cls_idx = box_idx + 1;
//         int sum_idx = box_idx + 2;

//         float* box_preds = reinterpret_cast<float*>(out[box_idx].buf);
//         float* cls_preds = reinterpret_cast<float*>(out[cls_idx].buf);
//         float* sum_preds = reinterpret_cast<float*>(out[sum_idx].buf);

//         int box_h = modelMetadata.output_attrs[box_idx].dims[2];
//         int box_w = modelMetadata.output_attrs[box_idx].dims[3];
        
//         float stride_x = float(modelMetadata.input_attrs[0].dims[2]) / box_w;
//         float stride_y = float(modelMetadata.input_attrs[0].dims[1]) / box_h;

//         int grid_len = box_h * box_w;
//         for (int i = 0; i < box_h; i++)
//         {
//             for (int j = 0; j < box_w; j++)
//             {
//                 int offset = i * box_w + j;
//                 int max_class_id = -1;

//                 if (sum_preds[offset] < confThreshold_) continue;

//                 float max_score = 0;
//                 for (int c = 0; c < numClasses_; c++)
//                 {
//                     if ((cls_preds[offset] > confThreshold_) && (cls_preds[offset] > max_score))
//                     {
//                         max_score = cls_preds[offset];
//                         max_class_id = c;
//                     }
//                     offset += grid_len;
//                 }

//                 if (max_score> confThreshold_)
//                 {
//                     offset = i * box_w + j;
//                     float box[4];
//                     for (int k = 0; k < 4; k++)
//                     {
//                         box[k] = box_preds[offset];
//                         offset += grid_len;
//                     }

//                     float x1, y1, x2, y2;
//                     x1 = (-box[0] + j + 0.5) * stride_x - letterboxInfo.x_pad;
//                     y1 = (-box[1] + i + 0.5) * stride_y - letterboxInfo.y_pad;
//                     x2 = (box[2] + j + 0.5) * stride_x - letterboxInfo.x_pad;
//                     y2 = (box[3] + i + 0.5) * stride_y - letterboxInfo.y_pad;

//                     results->push_back(RKNNResult(
//                         max_class_id,
//                         max_score,
//                         (int)(clamp(x1, 0, modelMetadata.model_width) / letterboxInfo.scale),
//                         (int)(clamp(y1, 0, modelMetadata.model_height) / letterboxInfo.scale),
//                         (int)(clamp(x2, 0, modelMetadata.model_width) / letterboxInfo.scale),
//                         (int)(clamp(y2, 0, modelMetadata.model_height) / letterboxInfo.scale)
//                     ));
//                 }
//             }
//         }
//     }
// }

extern "C" {

void* yolo_init(const char* model_path, float conf_threshold) {
    RKNNYOLO26Detection* detector = new RKNNYOLO26Detection(conf_threshold);
    int ret = detector->loadModel(model_path);
    if (ret != 0) {
        delete detector;
        return nullptr;
    }
      
    return (void*)detector;
}

int yolo_detect(void* handle, int width, int height, unsigned char* data, YOLO_Box_t* out_boxes, int max_boxes) {
    if (!handle) return -1;
    
    RKNNYOLO26Detection* detector = (RKNNYOLO26Detection*)handle;
    
    // 构造 image_t 传给 C++ 接口
    image_t img;
    img.width = width;
    img.height = height;
    img.data = data;

    std::vector<RKNNResult> results;
    detector->process(img, results);

    // 将 std::vector 结果拷贝回 C 结构体数组
    int count = (results.size() < (size_t)max_boxes) ? results.size() : max_boxes;
    for (int i = 0; i < count; i++) {
        out_boxes[i].x1 = results[i].box->x1; // 假设 RKNNResult 里有这些字段
        out_boxes[i].y1 = results[i].box->y1;
        out_boxes[i].x2 = results[i].box->x2;
        out_boxes[i].y2 = results[i].box->y2;
        out_boxes[i].score = results[i].confidence;
        out_boxes[i].class_id = results[i].classId;
    }
    return count;
}

void yolo_deinit(void* handle) {
    if (handle) {
        delete (RKNNYOLO26Detection*)handle;
    }
}

}