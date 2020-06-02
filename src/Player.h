#pragma once
#include "Box2DEngine.h"
#include "Global.h"


class Player
{
public:
	Player(Box2DEngine* gameController);
	~Player();
	b2Body* getBody();

private:
	Box2DEngine* gameController;
	b2Body* body;
};