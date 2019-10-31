// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Midori.h
// Date: 03/10/2019

#pragma once

#include "midori/Application.h"
#include "midori/Log.h"
#include "midori/layers/Layer.h"

#include "midori/Input.h"
#include "midori/MouseButtonCodes.h"
#include "midori/KeyCodes.h"

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

// == Entry Point == //
#include "midori/EntryPoint.h"
