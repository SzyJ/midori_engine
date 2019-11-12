// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Midori.h
// Date: 03/10/2019

#pragma once

#include "midori/core/Application.h"
#include "midori/core/Log.h"
#include "midori/layers/Layer.h"

#include "midori/core/Input.h"
#include "midori/core/MouseButtonCodes.h"
#include "midori/core/KeyCodes.h"

#include "midori/core/DeltaTime.h"

#include "midori/layers/imgui/ImGuiLayer.h"

// Events
#include "midori/events/ApplicationEvent.h"
#include "midori/events/KeyEvent.h"
#include "midori/events/MouseEvent.h"

// Renderer
#include "midori/renderer/Renderer.h"
#include "midori/renderer/RenderCommand.h"
#include "midori/renderer/Buffer.h"
#include "midori/renderer/Shader.h"
#include "midori/renderer/Texture.h"

#include "midori/renderer/camera/PerspectiveCamera.h"

// Scene
#include "midori/scene/SceneObject.h"
#include "midori/scene/Scene.h"
#include "midori/scene/Skybox.h"

// == Entry Point == //
#include "midori/core/EntryPoint.h"
