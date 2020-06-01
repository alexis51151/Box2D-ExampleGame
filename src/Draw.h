#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Box2DEngine.h"
#include <cmath>
#include "Global.h"


void DrawShape(b2Body* body, sf::Shape* shape, sf::RenderWindow* window);
