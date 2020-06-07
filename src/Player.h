#pragma once
#include "Box2DEngine.h"
#include "Global.h"
#include "Circle.h"
#include "Shape.h"
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(Box2DEngine* gameController);
	b2Body* getBody() {return Player::body;};
	void draw(sf::Color color, sf::RenderWindow* window);
	void actionLef();
	void actionRight();
	void actionDown();
	void actionUp();

private:
	b2Body* body;
	std::unique_ptr<Shape> shape;
};