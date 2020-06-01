#pragma once
#include <box2d/box2d.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <Material.h>

class Box2dEngine
{
public:
	Box2dEngine();
	Box2dEngine(int widgth, int heigth);

	~Box2dEngine();

	b2World* getPhysicsWorld() { return physicsWorld; }
	sf::RenderWindow* getApp() { return app; }
	
	b2Body* create_platform(float posx, float posy);
	b2Body* create_body( float x, float y);


private:
	static b2World* physicsWorld;
	static sf::RenderWindow* app;
	int resWidgth;
	int resHeigth;
};




