#pragma once

#define Quote(x) #x

#include <iostream>
#include <vector>
#include <chrono>

class Application;
class Gameobject;

//common - independent includes
#include "Time.h"
#include "Vector2.h"
#include "EventSystem.h"

//core - interdependent includes
#include "ECS.h"

#include "Application.h"

#include "Gameobject.h"

//log.h
