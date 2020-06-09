#pragma once


#include "Shape.h"
#include "box2d/box2d.h"
#include "Global.h"
#include "FixtureData.h"
#include "Utile.h"

class Circle : public Shape
{
public:
	Circle();
	void draw(b2Body* body, sf::Color color, sf::RenderWindow* window);
};