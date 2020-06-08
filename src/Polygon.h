#pragma once
#include "FixtureData.h"
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "Shape.h"
#include "Global.h"

class Polygon : public Shape {
public:
	Polygon();
	void draw(b2Body*, sf::Color, sf::RenderWindow*);
};