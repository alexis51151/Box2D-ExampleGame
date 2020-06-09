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
#include "XMLParser.h"


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


// One monster over a platform (must move around x but not around y)
TEST(TestInteractionBodies, TestMonsterPlatform) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	// adding one monster
	Monster* monster = new Monster(&gameController, 300, 200, 20, 20);

	// adding one platform
	Platform* platform = new Platform(&gameController, 300, 300, 10, 100);

	// Simulating over some iterations

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// 500 iterations to make the monster fall (500*2 = 1000 meters high)
	for (int i = 0; i < 500; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
		monster->decreaseReverseSpeedTimeout();
		monster->updateSpeed();
	}
	b2Vec2 oldPosition = monster->getBody()->GetPosition();
	// Another round of simulations to check that Player is stationary
	for (int i = 0; i < 10; i++) {
		world->Step(timeStep, velocityIterations, positionIterations);
		monster->decreaseReverseSpeedTimeout();
		monster->updateSpeed();
		b2Vec2 newPosition = monster->getBody()->GetPosition();

		EXPECT_NE(oldPosition.x, newPosition.x);
		EXPECT_EQ(oldPosition.y, newPosition.y);
	}
}

// One monster detects a player at his left
TEST(TestInteractionBodies, TestMonsterPlayer) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	// adding one monster
	Monster* monster = new Monster(&gameController, 300, 280, 20, 20);

	// adding one player
	Player* player = new Player(&gameController, 300, 290, 20, 20);


	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world->Step(timeStep, velocityIterations, positionIterations);

	EXPECT_EQ(monster->getMy_Lviewdata()->getEntityDetected(), 1);

}

/*
// One monster cannot detects a player at his left because of a wall
TEST(TestInteractionBodies, TestMonsterPlayer2) {
	// Setting up the gameController
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	// adding one monster
	Monster* monster = new Monster(&gameController, 300, 280, 20, 20);

	// adding one player
	Player* player = new Player(&gameController, 300, 300, 20, 20);

	// adding one platform (wall here)
	Platform* platform = new Platform(&gameController, 300, 290, 30, 5);

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world->Step(timeStep, velocityIterations, positionIterations);

	EXPECT_EQ(monster->getMy_Lviewdata()->getEntityDetected(), 0);

}
*/


TEST(TestReadXML, TestFileOpened) {
	// Getting the config file (I can't manage to set a relative path, so I will fail at first for you)
	XMLParser configParser("C:/Users/alexi/source/repos/Jeu_jin/resources/config.xml");

	// Is the file opened ?
	EXPECT_NE(configParser.getConfig(), "");
}

TEST(TestReadXML, TestFileReadWorld) {
	// Getting the config file (I can't manage to set a relative path, so I will fail at first for you)
	XMLParser configParser("C:/Users/alexi/source/repos/Jeu_jin/resources/config.xml");

	configParser.readConfig();
	EXPECT_EQ(configParser.getWorldParameters()["width"], 1920);
	EXPECT_EQ(configParser.getWorldParameters()["height"], 1080);
}

TEST(TestReadXML, TestFileReadCommands) {
	// Getting the config file (I can't manage to set a relative path, so I will fail at first for you)
	XMLParser configParser("C:/Users/alexi/source/repos/Jeu_jin/resources/config.xml");

	configParser.readConfig();

	// Player1
	
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer1()["Up"], 73);
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer1()["Left"], 71);
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer1()["Right"], 72);
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer1()["Down"], 74);
	
	// Player2
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer2()["Up"], 25);
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer2()["Left"], 16);
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer2()["Right"], 3);
	EXPECT_EQ(configParser.getKeyboardCommandsPlayer2()["Down"], 18);
}