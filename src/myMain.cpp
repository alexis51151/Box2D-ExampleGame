#include "myMain.h"
#include <direct.h>

int myMain() {

	// Retrieve game config
	XMLParser configParser("C:/Users/alexi/source/repos/Jeu_jin/resources/config.xml");
	configParser.readConfig();


	

	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);


	// Textures loading
	// Background
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	background_texture.loadFromFile("C:/Users/alexi/source/repos/Jeu_jin/resources/fond.jpg", sf::IntRect(0, 0, WIDTH, HEIGHT));
	background_sprite.setPosition(WIDTH / 2, HEIGHT / 2);
	background_sprite.setTexture(background_texture);
	window->draw(background_sprite);

	//creation de la liste des platformes 

	std::vector<std::unique_ptr<Platform>>platforms;

	platforms.push_back(std::make_unique<Platform>(&gameController,WIDTH / 2, HEIGHT, WIDTH/2, HEIGHT / 10 )); //sol 
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH / 6, HEIGHT* 3/10, WIDTH / 8, HEIGHT / 30)); //platform 
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH * 2/ 3, HEIGHT * 6 / 10, WIDTH / 6, HEIGHT / 30)); //sol 
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH * 2 / 3, HEIGHT * 4 / 10, WIDTH / 12, HEIGHT / 35)); //platform esquive monstre
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH * 2 / 3, HEIGHT * 3.7 / 10, WIDTH /40, HEIGHT / 15));
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH / 6, HEIGHT * 8 / 10, WIDTH / 15, HEIGHT / 30));
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH / 3, HEIGHT * 7 / 10, WIDTH / 15, HEIGHT / 30));
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH / 2, HEIGHT * 6 / 10, WIDTH / 15, HEIGHT / 30));
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH / 2, HEIGHT/2, 10, HEIGHT));//mure gauche

	// Création d'un monstre 
	std::vector<std::unique_ptr<Monster>> monsters;
	monsters.push_back(std::unique_ptr <Monster>(new Monster(&gameController, WIDTH * 2 / 3, HEIGHT * 5 / 10)));
	monsters.push_back(std::unique_ptr <Monster>(new Monster(&gameController, WIDTH / 2, HEIGHT * 9 / 10)));

	// Création des joueurs 
	std::vector<std::unique_ptr<Player>> players;
	players.push_back(std::unique_ptr<Player>(new Player(&gameController,15 * RATIO, HEIGHT * 3 / 10)));
	players.push_back(std::unique_ptr<Player>(new Player(&gameController,10 * RATIO, HEIGHT * 3 / 10)));


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
		//couleur du joueur 1 si detection
		if (players[0]->isplayerdetected()){
			playercolor[0] = sf::Color::Red;
			sf::Font font;
			font.loadFromFile("C:/Users/alexi/source/repos/Jeu_jin/resources/DIOGENES.ttf");
			sf::Text text;
			text.setFont(font);
			text.setString("GAME OVER");
			text.setCharacterSize(200);
			text.setFillColor(sf::Color::Red);
			text.setStyle(sf::Text::Bold);
			text.setPosition(WIDTH / 2 - 500, HEIGHT / 2 - 200);
			window->clear(sf::Color::Black);
			window->draw(text);
			window->display();
			Sleep(5000);
			window->close();
			return 0;

		}
		else {
			playercolor[0] = sf::Color::Green;
		}
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

