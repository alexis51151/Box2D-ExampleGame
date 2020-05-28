#include "myMain.h"



int myMain() {
	// Initialisation SFML
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Outil de visualisation"); // Variable globale pour la fenêtre 
	window.clear(sf::Color::White);
	window.display();

	// Boucle d'événements SFML
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}