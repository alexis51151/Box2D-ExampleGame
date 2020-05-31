#pragma once
#include <box2d/box2d.h>
#include <stdio.h>
#include <stdlib.h>


b2Body* create_platforme(b2World& world, float posx, float posy);
b2Body* create_body(b2World& world, float x, float y);