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
	b2Body* body;
};