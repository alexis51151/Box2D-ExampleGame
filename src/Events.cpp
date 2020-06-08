#include <Events.h>
#include "playerrightcommand.h"


Icommand* newplatformcommand = new Newplatformcommand();
Icommand* jump = new PlayerJumcomand();
Icommand* left = new PlayerLeftcomand();
Icommand* down = new PlayerDowncomand();
Icommand* right = new PlayerRighttcomand();

void HookEvents(sf::Window* window, Box2DEngine* gameController, std::vector<std::unique_ptr<Player>>* players, std::vector<std::unique_ptr<Platform>>* platforms) {
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
			platforms->push_back(std::make_unique<Platform>(gameController,MouseX, MouseY, 8.0f * RATIO, 1.0f * RATIO));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			left->execute((players->operator[](0)).get());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			right->execute((players->operator[](0)).get());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			down->execute((players->operator[](0)).get());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			jump->execute((players->operator[](0)).get());
		}
	}
}

