#include "Player.h"
#include "Rectangle.h"


Player::Player(Box2DEngine* gameController)
{
	Player::body = gameController->addBodyPlayer(10 * RATIO, 10 * RATIO, 1.0f * RATIO, 1.0f * RATIO);
	Player::shape = std::unique_ptr<Circle>(new Circle());
}


b2Body* Player::getBody()
{
	return Player::body;
}

void Player::draw(sf::Color color, sf::RenderWindow* window) {
	Player::shape->draw(body, color, window);
}
