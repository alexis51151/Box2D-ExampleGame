#pragma once
#include "Box2DEngine.h"
#include "Global.h"


class Player
{
public:
	Player(Box2DEngine* gameController);
	~Player();
	b2Body* getBody();
	void draw(sf::Color color, sf::RenderWindow* window);
private:
	b2Body* body;
};