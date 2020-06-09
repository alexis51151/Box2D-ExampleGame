#pragma once 
#include <box2d/box2d.h>
#include "FootData.h"
#include "HandData.h"
#include "PlayerData.h"


std::pair<float, float> getBodyDimensions(b2Body* body);