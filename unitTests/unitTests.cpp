#include <gtest/gtest.h>
#include <pugixml.hpp>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "myMain.h"
#include "Player.h"
#include "Monster.h"
#include "Platform.h"
#include "Rope.h"


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
	// adding one player
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
	// adding one player
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