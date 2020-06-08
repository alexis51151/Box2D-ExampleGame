#include <gtest/gtest.h>
#include <pugixml.hpp>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "myMain.h"
#include "Player.h"
#include "Monster.h"
#include "Platform.h"
#include "Rope.h"
#include "Rectangle.h"
#include "Shape.h"


TEST(TestAddBody, TestAddPlayer) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	// adding one player
	Player* player = new Player(&gameController);
	b2Body* player_body = player->getBody();
	// Going through the box2D bodies list
	int found = 0;
	for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()) {
		if (BodyIterator == player_body) {
			found++;
		}
	}
	EXPECT_EQ(found, 1);
}

TEST(TestAddBody, TestAddMonster) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	// adding one player
	Monster* monster = new Monster(&gameController, 300, 300);
	b2Body* monster_body = monster->getBody();
	// Going through the box2D bodies list
	int found = 0;
	for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()) {
		if (BodyIterator == monster_body) {
			found++;
		}
	}
	EXPECT_EQ(found, 1);
}

TEST(TestAddBody, TestAddPlatform) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	// adding one platform
	Platform* platform = new Platform(&gameController, 300, 300, 10,100);
	b2Body* platform_body = platform->getBody();
	// Going through the box2D bodies list
	int found = 0;
	for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()) {
		if (BodyIterator == platform_body) {
			found++;
		}
	}
	EXPECT_EQ(found, 1);
}

TEST(TestAddBody, TestAddRope) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	// adding one rope
	Rope* rope = new Rope(10 * RATIO, 30, &gameController);

	std::vector<b2Body*> elements = rope->getElements();
	// Going through the box2D bodies list
	int found = 0;
	std::vector<b2Body*>::iterator it;
	for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()) {
		it = std::find(elements.begin(), elements.end(), BodyIterator);
		EXPECT_NE(it, elements.end());
	}
}

// One player over a platform
TEST(TestInteractionBodies, TestPlayerPlatform1) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();	
	sf::RenderWindow* window = gameController.getApp();

	// adding one player
	Player* player = new Player(&gameController, 429, 250);

	// adding one platform
	Platform* platform = new Platform(&gameController, 300, 300, 10, 100);
	
	// Simulating over some iterations

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2Vec2 positions = platform->getBody()->GetPosition();
	// 500 iterations to make the player fall (500*2 = 1000 meters high)
	for (int i = 0; i < 500; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
	}
	b2Vec2 oldPosition = player->getBody()->GetPosition();
	// Another round of simulations to check that Player is stationary
	for (int i = 0; i < 10; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 newPosition = player->getBody()->GetPosition();

		EXPECT_EQ(oldPosition.x, newPosition.x);
		EXPECT_EQ(oldPosition.y, newPosition.y);
	}
}

// One player falls
TEST(TestInteractionBodies, TestPlayerPlatform2) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();

	// adding one player
	Player* player = new Player(&gameController, 431, 250);

	// adding one platform
	Platform* platform = new Platform(&gameController, 300, 300, 10, 100);

	// Simulating over some iterations

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2Vec2 positions = platform->getBody()->GetPosition();
	// 500 iterations to make the player fall (500*2 = 1000 meters high)
	for (int i = 0; i < 500; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
	}
	b2Vec2 oldPosition = player->getBody()->GetPosition();
	// Another round of simulations to check that Player is stationary
	for (int i = 0; i < 10; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 newPosition = player->getBody()->GetPosition();

		EXPECT_EQ(oldPosition.x, newPosition.x);
		EXPECT_NE(oldPosition.y, newPosition.y);
	}
}

/*
// One monster over a platform (must move around x but not around y)
TEST(TestInteractionBodies, TestMonsterPlatform) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();

	// adding one monster
	Monster* monster = new Monster(&gameController, 300, 250, 10, 10);

	// adding one platform
	Platform* platform = new Platform(&gameController, 300, 300, 10, 100);

	// Simulating over some iterations

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2Vec2 positions = platform->getBody()->GetPosition();
	// 500 iterations to make the monster fall (500*2 = 1000 meters high)
	for (int i = 0; i < 500; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
	}
	b2Vec2 oldPosition = monster->getBody()->GetPosition();
	// Another round of simulations to check that Player is stationary
	for (int i = 0; i < 10; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 newPosition = monster->getBody()->GetPosition();

		EXPECT_EQ(oldPosition.x, newPosition.x);
		EXPECT_EQ(oldPosition.y, newPosition.y);
	}
}
*/
