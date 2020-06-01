#pragma once

#include <Box2DEngine.h>
#include <SFML/Graphics.hpp>
#include "Global.h"


void HookEvents(sf::Window* window, Box2DEngine* gameController, b2Body* player);

