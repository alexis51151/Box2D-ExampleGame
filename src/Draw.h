#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Box2DEngine.h"
#include <cmath>
#include "Global.h"
#include <memory>
#include "Utile.h"



void DrawShape(b2Body* body, sf::Color color, sf::RenderWindow* window);
