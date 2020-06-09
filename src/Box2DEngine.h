#pragma once
#include <box2d/box2d.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <Material.h>
#include <FixtureData.h>
#include "PlayerData.h"
#include "FootData.h"
#include "HandData.h"
#include <memory>
#include "Shape.h"

class Box2DEngine
{
public:
	Box2DEngine(int width, int heigth);

	~Box2DEngine();

	b2World* getPhysicsWorld() { return physicsWorld.get(); }
	sf::RenderWindow* getApp() { return app.get(); }
	
	b2Body* addDynamicBox(int x, int y, float heigth, float widgth, Material material);
	b2Body* addStaticBox(int x, int y, float heigth, float widgth);

private:
	std::unique_ptr<b2World> physicsWorld;
	std::unique_ptr<sf::RenderWindow> app;
};




