#pragma once

#include "Fjord/core/Application.h"
#include "Fjord/core/Log.h"
#include "Fjord/core/Event.h"

//RENDER
#include "Fjord/Render/Buffer.h"
#include "Fjord/Render/Camera.h"
#include "Fjord/Render/Shader.h"
#include "Fjord/Render/Texture.h"
#include "Fjord/Render/VertexArray.h"
#include "Fjord/Render/Framebuffer.h"
//END RENDER

//INPUT
#include "Fjord/core/Input.h"
#include "Fjord/core/KeyCodes.h"
#include "Fjord/core/MouseButtonCodes.h"
//END INPUT

//ECS
#include "Fjord/ECS/Components/Components.h"
#include "Fjord/ECS/Systems/EditorCameraControllerSystem.h"
#include "Fjord/ECS/Systems/RenderSystem.h"
#include "Fjord/ECS/Systems/GameSystem.h"
#include "Fjord/ECS/Scene.h"
#include "Fjord/ECS/SceneLoader.h"
//END ECS

#include "Fjord/Utils/PlatformUtils.h"

#include "Fjord/core/Core.h"