#include "Player.h"
#include "Rectangle.h"


Player::Player(Box2DEngine* gameController)
{
	body = gameController->addBodyPlayer(10 * RATIO, 10 * RATIO, 1.0f * RATIO, 1.0f * RATIO);
	shape = std::unique_ptr<Shape>(new Circle());
}


Player::~Player()
{

}

b2Body* Player::getBody()
{
	return body;
}

void Player::draw(sf::Color color, sf::RenderWindow* window) {
	shape->draw(body, color, window);
}
