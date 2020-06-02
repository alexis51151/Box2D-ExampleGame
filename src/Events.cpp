#include <Events.h>
#include "myMain.h"


void HookEvents(sf::Window* window, Box2DEngine* gameController, b2Body* player) {
	extern int numFootContact;
	extern int m_jumpTimeout;
	extern int numhandContact;
	sf::Event event;
	float impulse = player->GetMass() * 10;
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
			gameController->addStaticBox(MouseX, MouseY, 8.0f * RATIO, 2.0f * RATIO);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->ApplyLinearImpulseToCenter(b2Vec2(-10, 0), true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->ApplyLinearImpulseToCenter(b2Vec2(10, 0), true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player->ApplyLinearImpulseToCenter(b2Vec2(0, 10), true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (numFootContact < 1 && numhandContact<1) break;
			if (m_jumpTimeout > 0) break;
			player->ApplyLinearImpulseToCenter(b2Vec2(0, -impulse), true);
			m_jumpTimeout = 15;
		}
	}
}