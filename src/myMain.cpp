#include "myMain.h"

int myMain() {
	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);
	//creation de la liste des joueur 
	std::vector<std::unique_ptr<Player>> players; 
	std::unique_ptr<Player> player1(new Player(&gameController));
	std::unique_ptr<Player> player2(new Player(&gameController));
	players.push_back(std::move(player1));
	players.push_back(std::move(player2));

	b2Body* player1_body = player1->getBody();
	b2Body* player2_body = player2->getBody();

	//creation d'un monstre 
	std::vector<std::unique_ptr<Monster>> monsters;
	std::unique_ptr <Monster> premier_monstre (new Monster(&gameController,300,300));
	monsters.push_back(std::move(premier_monstre));

	b2Body* monstre_body = premier_monstre->getBody();
	// Link the two players with a rope
	std::unique_ptr<Rope> rope(new Rope(800,400, 10 * RATIO, 30, &gameController));
	rope->linkPlayers(player1.get(), player2.get(), world);

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	while (window->isOpen())
	{
		// Events.cpp : handle mouse and keyboard events
		HookEvents(window, &gameController, player1_body);
		window->clear(sf::Color::White);
		
		world->Step(timeStep, velocityIterations, positionIterations);
		for (int i = 0; i < players.size; i++) { //gestion des player 
			getPlayerData(players[i]->getBody())->decreaseJumpTimeout();// decrease le timout pour les jumps de joeur 
			players[i]->draw(sf::Color::Green, window);
		}
		//getPlayerData(player1_body)->decreaseJumpTimeout();
		//getPlayerData(player2_body)->decreaseJumpTimeout();

		for (int i = 0; i < monsters.size; i++) {
			monsters[i]->decreace_reverspeed_timout();
			monsters[i]->updatespeed();
			monsters[i]->draw(sf::Color::Red,window);
		}
		window->display();
	}
	return 0;
}

