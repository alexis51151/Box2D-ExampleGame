#pragma once
#include "SFML/Graphics.hpp"

class Shape {
public:
	Shape();
	virtual void Draw() = 0;
private:
	sf::Color color;
};