// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PostProcessingPipeline.h
// Date: 25/11/2019

#pragma once

#include "midori/renderer/Buffer.h"
#include "midori/renderer/post-processing/PostProcessStage.h"
#include "midori/renderer/VertexArray.h"

#include <vector>

#define MD_POST_PROCESS_TEX_OFFSET 5

namespace midori {

    class PostProcessingPipeline {
    public:
        PostProcessingPipeline();
        ~PostProcessingPipeline() = default;

        void BeginPostProcess();
        void FinishPostProcess();

        void UpdateScreenSize(uint32_t width, uint32_t height);

    private:
        ref<Shader> m_SimpleDrawShader;
        ref<VertexArray> m_ScreenQuad;
        ref<FrameBufferColor2D> m_InputFrame;
        std::vector<PostProcessStage> m_ProcessStages;

        void DrawScreenQuad();
    };

}
