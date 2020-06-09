#pragma once

#include <Box2DEngine.h>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include <memory>
#include "Utile.h"
#include "Player.h"
#include "Platform.h"
#include "playerleftcommand.h"
#include "playerjumcomand.h"
#include "playerdowncomand.h"
#include "Icomand.h"

void HookEvents(sf::Window* window, Box2DEngine* gameController, std::vector<std::unique_ptr<Player>>* players, std::vector<std::unique_ptr<Platform>>* platforms, std::map<std::string, int>* keyboardCommandsPlayer1, std::map<std::string, int>* keyboardCommandsPlayer2);


