#include <iostream>
#include <cassert>
#include <rga/im2d.h>
#include <rga/RgaApi.h>

#include "misc.h"

int clamp(int val, int min, int max) {
    return (val < min) ? min : ((val > max) ? max : val);
}

int readDataFromFile(const char *path, char **out_data)
{
    FILE *fp = fopen(path, "rb");
    if(fp == NULL) 
    {
        std::cerr << "fopen " << path << " fail" << std::endl;
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    char *data = (char *) malloc(file_size + 1);
    data[file_size] = 0;
    fseek(fp, 0, SEEK_SET);
    if (file_size != fread(data, 1, file_size, fp)) 
    {
        std::cerr << "fread " << path << " fail" << std::endl;
        free(data);
        fclose(fp);
        return -1;
    }
    if (fp) 
    {
        fclose(fp);
    }
    *out_data = data;

    return file_size;
}

void cpu_resize(const image_t &src, image_t &dst) {
    float x_ratio = (float)src.width / dst.width;
    float y_ratio = (float)src.height / dst.height;
    for (int i = 0; i < dst.height; i++) {
        for (int j = 0; j < dst.width; j++) {
            int px = (int)(j * x_ratio);
            int py = (int)(i * y_ratio);
            dst.data[(i * dst.width + j) * 3 + 0] = src.data[(py * src.width + px) * 3 + 0];
            dst.data[(i * dst.width + j) * 3 + 1] = src.data[(py * src.width + px) * 3 + 1];
            dst.data[(i * dst.width + j) * 3 + 2] = src.data[(py * src.width + px) * 3 + 2];
        }
    }
}

void letterbox(
    const image_t &src, 
    image_t &dst, 
    letterbox_t &ltb, 
    int target_w, int target_h, 
    const int pad_color,
    bool auto_pad,
    int stride,    
    bool rgaAccel
) {

    if (src.width == target_w && src.height == target_h) {
        memcpy(dst.data, src.data, target_w * target_h * 3);
        ltb.scale = 1.0f;
        ltb.x_pad = 0;
        ltb.y_pad = 0;
        return;
    }

    float scale = std::min((float)target_w / src.width, (float)target_h / src.height);
    ltb.scale = scale;
    int resized_w = (int)(src.width * scale);
    int resized_h = (int)(src.height * scale);

    int pad_width = target_w - resized_w;
    int pad_height = target_h - resized_h;

    if (auto_pad) {
        pad_width %= stride;
        pad_height %= stride;
    }

    int pad_left = pad_width / 2;
    int pad_top  = pad_height / 2;
    
    ltb.x_pad = pad_left;
    ltb.y_pad = pad_top;

    memset(dst.data, pad_color, target_w * target_h * 3);

    if (rgaAccel) {
        // RGA Approach
        rga_buffer_t rga_src, rga_dst;
        memset(&rga_src, 0, sizeof(rga_src));
        memset(&rga_dst, 0, sizeof(rga_dst));

        rga_src.handle = importbuffer_virtualaddr(src.data, src.width * src.height * 3);
        rga_src.width  = src.width;
        rga_src.height = src.height;
        rga_src.wstride = src.width;
        rga_src.hstride = src.height;
        rga_src.format = RK_FORMAT_RGB_888;

        assert(target_w % 16 == 0);
        rga_dst.handle = importbuffer_virtualaddr(dst.data, target_w * target_h * 3);
        rga_dst.width  = target_w;
        rga_dst.height = target_h;
        rga_dst.wstride = target_w;
        rga_dst.hstride = target_h;
        rga_dst.format = RK_FORMAT_RGB_888;

        im_rect src_rect = {0, 0, src.width, src.height};
        im_rect dst_rect = {pad_left, pad_top, resized_w, resized_h};

        int ret = improcess(rga_src, rga_dst, {}, src_rect, dst_rect, {}, IM_SYNC);
        if (ret != IM_STATUS_SUCCESS) {
            std::cerr << "RGA Failed, ret=" << ret << std::endl;
        }
    } else {
        // CPU Approaches
        unsigned char* temp_resized = (unsigned char*)malloc(resized_w * resized_h * 3);
        image_t resized_img = {resized_w, resized_h, temp_resized};
        
        cpu_resize(src, resized_img);

        for (int y = 0; y < resized_h; y++) {
            unsigned char* src_ptr = temp_resized + (y * resized_w * 3);
            unsigned char* dst_ptr = dst.data + ((y + pad_top) * target_w + pad_left) * 3;
            memcpy(dst_ptr, src_ptr, resized_w * 3);
        }
        
        free(temp_resized);
    }

}