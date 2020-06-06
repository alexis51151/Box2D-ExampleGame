#pragma once
#include "box2d//box2d.h"
#include "Global.h"
#include "SFML/Graphics.hpp"
#include <memory>
#include "Box2DEngine.h"

class Platform{
public:
	Platform(Box2DEngine* gameController);
	void draw(sf::Color color, sf::RenderWindow* window);
private:
	b2Body* body;
	std::unique_ptr<Shape> shape;
};