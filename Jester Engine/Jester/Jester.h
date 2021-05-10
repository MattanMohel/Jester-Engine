#pragma once

#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <array>
#include <cmath>

class Application;
class Component;
class Object;
class Line;
#include "Renderer/Line.h"

//      CORE
// Core structs
#include "Core/Vector2.h"
#include "Core/Color.h"

// Core independent
#include "Core/EventSystem.h"
#include "Core/Transform.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Core/Time.h"
#include "Core/Log.h"

// Core includes
#include "Core/Component.h"
#include "Core/Application.h"
#include "Core/Gameobject.h"
#include "Core/Collider.h"
#include "Core/Rigidbody.h"

//      RENDERER
#include "Renderer/RendererBase.h"
#include "Renderer/Camera.h"
#include "Renderer/Sprite.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"

//      USER_INTERFACE
#include "User Interface/UI.h"

