#include "myMain.h"
#include <direct.h>

int myMain() {

	// Retrieve game config
	
	XMLParser configParser("C:/Users/aigle/Desktop/projet_jhin/test/Jeu_jin/resources/config.xml");
	configParser.readConfig();

	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	//creation de la liste des platformes 

	std::vector<std::unique_ptr<Platform>>platforms;

	platforms.push_back(std::make_unique<Platform>(&gameController,WIDTH / 2, HEIGHT, WIDTH/2, HEIGHT / 10 )); //sol 
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH / 6, HEIGHT* 3/10, WIDTH / 8, HEIGHT / 30)); //platform 
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH * 2/ 3, HEIGHT * 6 / 10, WIDTH / 6, HEIGHT / 30)); //sol 
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH * 2 / 3, HEIGHT * 4 / 10, WIDTH / 12, HEIGHT / 35)); //platform esquive monstre  
	
	// Création d'un monstre 
	std::vector<std::unique_ptr<Monster>> monsters;
	monsters.push_back(std::unique_ptr <Monster>(new Monster(&gameController, WIDTH * 2 / 3, HEIGHT * 5 / 10)));


	// Création des joueurs 
	std::vector<std::unique_ptr<Player>> players;
	players.push_back(std::unique_ptr<Player>(new Player(&gameController, 15 * RATIO, HEIGHT * 3 / 10)));
	players.push_back(std::unique_ptr<Player>(new Player(&gameController, 10 * RATIO, HEIGHT * 3 / 10)));


	// Link the two players with a rope
	std::unique_ptr<Rope> rope(new Rope(5 * RATIO, 15, &gameController));
	rope->linkPlayers(players[0].get(), players[1].get(), world);

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	sf::Color playercolor[2] = { sf::Color::Green,sf::Color::Blue };

	while (window->isOpen())
	{
		// Events.cpp : handle mouse and keyboard events
		HookEvents(window, &gameController, &players, &platforms, &(configParser.getKeyboardCommandsPlayer1()), &(configParser.getKeyboardCommandsPlayer2()));
		window->clear(sf::Color::White);

		world->Step(timeStep, velocityIterations, positionIterations);
		// Gestion des joueurs 
		for (int i = 0; i < players.size(); i++) {
			players[i]->decreasejumptimout();// decrease le timeout pour les jumps 
			players[i]->draw(playercolor[i], window);
		}

		// Gestion des monstres 
		for (int i = 0; i < monsters.size(); i++) {
			monsters[i]->decreaseReverseSpeedTimeout();
			monsters[i]->updateSpeed();
			monsters[i]->draw(sf::Color::Magenta, window);
		}
		// Gestion des plateformes 
		for (int i = 0; i < platforms.size(); i++)
			platforms[i]->draw(sf::Color::Red, window);

		// Gestion de la corde 
		rope->draw(sf::Color::Green, window);


		window->display();
	}
	return 0;
}

