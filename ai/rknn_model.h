#ifndef _RKNN_MODEL_H_
#define _RKNN_MODEL_H_

#include <cstdio>
#include "rknn_api.h"
#include "misc.h"
// #include "objects.h"
// #include "utils/file_utils.h"
// #include "utils/image_utils.h"

typedef struct {
    rknn_context rknn_ctx;
    rknn_input_output_num io_num;
    rknn_tensor_attr* input_attrs;
    rknn_tensor_attr* output_attrs;
    rknn_tensor_format tensor_format;
    rknn_tensor_type tensor_type;
    int model_channel;
    int model_width;
    int model_height;
    bool is_quant;
    bool output_want_float;
    rknn_core_mask core_mask;
} rknn_model_metadata;

/**
 * @class RKNNModel
 * @brief A base class for RKNN inference engine. All RKNN model should
 * inherits this base class.
 */
class RKNNModel
{
public:
    RKNNModel() {};
    virtual ~RKNNModel();

    /**
     * @brief Load RKNN model
     * @param modelPath Path to the model weight file
     */
    virtual int loadModel(const char *modelPath, rknn_core_mask coreMask);

    /**
     * @brief Load RKNN model with core mask set to auto
     */
    virtual int loadModel(const char *modelPath);

    /**
     * @brief Set NPU core mask
     * @param coreMask RKNN NPU core mask
     * 
     * Options:
     * - RKNN_NPU_CORE_AUTO: run on NPU core randomly
     * - RKNN_NPU_CORE_0: run on NPU core 0
     * - RKNN_NPU_CORE_1: run on NPU core 1
     * - RKNN_NPU_CORE_2: run on NPU core 2
     * - RKNN_NPU_CORE_0_1_2: run on NPU cores 0, 1, and 2
     * 
     * Note: RKNN_NPU_CORE_0_1_2 does not distribute the workload evenly across 
     * all NPU cores. Instead, it heavily utilizes core 0 and uses the other two 
     * cores for lighter processes.
     */
    int setCoreMask(rknn_core_mask coreMask);
    
    /**
     * @brief Print model metadata
     */
    void info();
    
    /**
     * @brief Model input width getter
     * @return Model input width
     */
    int getInputWidth() const {
        return modelMetadata.model_width;
    }

    /**
     * @brief Model input height getter
     * @return Model input height
     */
    int getInputHeight() const {
        return modelMetadata.model_height;
    }

    /**
     * @brief Set Model Metadata want_float
     */
    void setOutputWantFloat(bool val) {
        modelMetadata.output_want_float = val;
    }

protected:
    rknn_model_metadata modelMetadata;
    letterbox_t letterboxInfo;
    bool modelInitialized = false;

    /**
     * @brief RKNN inference.
     * @param inputs [in] Model input.
     * @param outputs [out] Model output.
     * @return Return code
     */
    int infer(rknn_input inputs[], rknn_output outputs[]);

    /**
     * @brief Release rknn_output.
     * @param outputs The rknn_output to be released.
     * @return Return code.
     */
    int releaseOutputs(rknn_output* outputs);

    /**
     * @brief Release RKNN model.
     * @return Error code, 0 indicates the model is successfully released.
     */
    int release();
};

void printTensorAttributes(const rknn_tensor_attr* attrs, int numAttrs);

#endif //_RKNN_MODEL_H_