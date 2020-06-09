#pragma once 
#include <box2d/box2d.h>
#include "FootData.h"
#include "HandData.h"
#include "PlayerData.h"


PlayerData* getPlayerData(b2Body* player1);
std::pair<float, float> getBodyDimensions(b2Body* body);