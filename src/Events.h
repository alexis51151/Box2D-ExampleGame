#pragma once

#include <Box2DEngine.h>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include <memory>
#include "Utile.h"
#include "Player.h"
#include "Platform.h"

void HookEvents(sf::Window* window, Box2DEngine* gameController, std::vector<std::unique_ptr<Player>>* players, std::vector<std::unique_ptr<Platform>>* platforms);


