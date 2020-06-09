#include <Events.h>
#include "playerrightcommand.h"


Icommand* newplatformcommand = new Newplatformcommand();
Icommand* jump = new PlayerJumcomand();
Icommand* left = new PlayerLeftcomand();
Icommand* down = new PlayerDowncomand();
Icommand* right = new PlayerRighttcomand();

void HookEvents(sf::Window* window, Box2DEngine* gameController, std::vector<std::unique_ptr<Player>>* players, std::vector<std::unique_ptr<Platform>>* platforms, std::map<std::string, int>*	keyboardCommandsPlayer1, std::map<std::string, int>* keyboardCommandsPlayer2) {
	sf::Event event;
	float impulse = players->operator[](1)->getBody()->GetMass() * 10;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			float MouseX = sf::Mouse::getPosition(*window).x;
			float MouseY = sf::Mouse::getPosition(*window).y;
			gameController->addDynamicBox(MouseX, MouseY, 1.0f * RATIO, 1.0f * RATIO, Material::WOOD);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			float MouseX = sf::Mouse::getPosition(*window).x;
			float MouseY = sf::Mouse::getPosition(*window).y;
			platforms->push_back(std::make_unique<Platform>(gameController,MouseX, MouseY,8.0f * RATIO, 1.0f * RATIO));
		}
		if(event.type == sf::Event::KeyPressed) {
			int mykey = keyboardCommandsPlayer1->operator[]("Up");
			if (event.key.code == keyboardCommandsPlayer1->operator[]("Up")) {
				jump->execute((players->operator[](0)).get());
			}
			else if(event.key.code == keyboardCommandsPlayer1->operator[]("Left")) {
				left->execute((players->operator[](0)).get());
			}
			else if (event.key.code == keyboardCommandsPlayer1->operator[]("Right")) {
				right->execute((players->operator[](0)).get());
			}
			else if (event.key.code == keyboardCommandsPlayer1->operator[]("Down")) {
				down->execute((players->operator[](0)).get());
			}
			// player 2
			else if (event.key.code == keyboardCommandsPlayer2->operator[]("Up")) {
				jump->execute((players->operator[](1)).get());
			}
			else if (event.key.code == keyboardCommandsPlayer2->operator[]("Left")) {
				left->execute((players->operator[](1)).get());
			}
			else if (event.key.code == keyboardCommandsPlayer2->operator[]("Right")) {
				right->execute((players->operator[](1)).get());
			}
			else if (event.key.code == keyboardCommandsPlayer2->operator[]("Down")) {
				down->execute((players->operator[](1)).get());
			}

			
			/**
			switch (event.key.code)
			{
				//player 1
			case sf::Keyboard::Up:
				jump->execute((players->operator[](0)).get());
				break;
			case sf::Keyboard::Left:
				left->execute((players->operator[](0)).get());
				break;
			case sf::Keyboard::Right:
				right->execute((players->operator[](0)).get());
				break;
			case sf::Keyboard::Down:
				down->execute((players->operator[](0)).get());
				break;
				//player 2
			case sf::Keyboard::Z:
				jump->execute((players->operator[](1)).get());
				break;
			case sf::Keyboard::Q:
				left->execute((players->operator[](1)).get());
				break;
			case sf::Keyboard::D:
				right->execute((players->operator[](1)).get());
				break;
			case sf::Keyboard::S:
				down->execute((players->operator[](1)).get());
				break;

			default:
				break;
			}
			/*/
		}
		
	}
}

