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

void Player::draw(sf::Color color, sf::RenderWindow* window) {
	float width = 0;
	float height = 0;
	b2Body* body = Player::body;
	b2Fixture* fixture = body->GetFixtureList();
	switch (fixture->GetType()) {
	case b2Shape::e_polygon: {
		while (fixture->GetNext() != NULL)
		{
			fixture = fixture->GetNext();
		}
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();

		width = sqrt(pow((poly->m_vertices[1].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[1].y - poly->m_vertices[0].y), 2));
		height = sqrt(pow((poly->m_vertices[3].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[3].y - poly->m_vertices[0].y), 2));
		//printf("width: %f \n", width);
		//printf("heigth: %f \n", height);
		break;
	}
	default:
		printf("No drawing available for this fixture type\n");
		return;
	}
	b2Vec2 position = body->GetPosition();

	std::unique_ptr<sf::CircleShape> shape(new sf::CircleShape(width / 2 * RATIO));
	shape->setFillColor(color);
	
	// Setting position and drawing with SFML
	shape->setPosition((position.x - width / 2) * RATIO, (position.y - height / 2) * RATIO);
	shape->rotate(body->GetAngle() * DEGTORAD);

	window->draw(*shape);
}
