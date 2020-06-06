#pragma once 
#include <box2d/box2d.h>
#include "FootData.h"
#include "HandData.h"
#include "PlayerData.h"

void getvalue(b2Body* player, int* footcount, int* handcount, int* jumptimout);
PlayerData* getPlayerData(b2Body* player1);
std::pair<int, int> getBodyDimensions(b2Body* body);