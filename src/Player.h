#pragma once
#include "Box2DEngine.h"
#include "Global.h"
#include "Circle.h"
#include "Shape.h"

class Player
{
public:
	Player(Box2DEngine* gameController);
	~Player();
	b2Body* getBody();
	void draw(sf::Color color, sf::RenderWindow* window);
private:
	b2Body* body;
	std::unique_ptr<Shape> shape;
};