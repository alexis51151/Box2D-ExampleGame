#include <Events.h>
#include "playerrightcommand.h"


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
		if(event.type == sf::Event::KeyPressed) {
			//player1
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
		}
		
	}
}

