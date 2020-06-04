#include <Player.h>

Player::Player(Box2DEngine* gameController)
{
	body = gameController->addBodyPlayer(10 * RATIO, 10 * RATIO, 1.0f * RATIO, 1.0f * RATIO);
}


Player::~Player()
{

}

b2Body* Player::getBody()
{
	return body;
}
