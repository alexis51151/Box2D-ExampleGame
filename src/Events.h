#pragma once

#include <Box2DEngine.h>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include <memory>


void HookEvents(sf::Window* window, Box2DEngine* gameController, b2Body* player);
void actionplayerRightKey(b2Body* player);
void actionplayerLeftKey(b2Body* player);
void actionplayerDownKey(b2Body* player);
void actionplayerUpKey(b2Body* player);

