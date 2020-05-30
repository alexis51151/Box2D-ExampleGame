#pragma once
#include <box2d/box2d.h>
#include <stdio.h>
#include <stdlib.h>


b2Body* create_body(b2World&);
b2Body* create_ground_body(b2World&);
b2Body* create_body_with_pose(b2World& world, float x, float y);