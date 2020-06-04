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

class Box2DEngine
{
public:
	Box2DEngine(int width, int heigth);

	~Box2DEngine();

	b2World* getPhysicsWorld() { return physicsWorld.get(); }
	sf::RenderWindow* getApp() { return app.get(); }
	
	b2Body* addDynamicBox(int x, int y, float heigth, float widgth, Material material);
	b2Body* addStaticBox(int x, int y, float heigth, float widgth);
	b2Body* addBodyPlayer(int x, int y, float height, float width);
	b2Body* addBodyMonster(int x, int y, float height, float width);
	b2Body* addBodyRope(int x, int y, float length, int nb_links);

private:
	std::unique_ptr<b2World> physicsWorld;
	std::unique_ptr<sf::RenderWindow> app;
};




