#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Shape {
public:
	Shape();
	Shape(sf::Color);
	virtual void draw(b2Body*, sf::Color, sf::RenderWindow*) = 0;
private:
	sf::Color color;
};