#include "Rectangle.h"


void Rectangle::draw(b2Body* body, sf::Color color, sf::RenderWindow* window) {
	std::pair<int, int> dimensions = getBodyDimensions(body);
	float width = dimensions.first;
	float height = dimensions.second;

	b2Vec2 position = body->GetPosition();

	sf::RectangleShape shape(sf::Vector2f(width * RATIO, height * RATIO))
	shape.setFillColor(color);


	// Setting position and drawing with SFML
	shape.setPosition((position.x - width / 2) * RATIO, (position.y - height / 2) * RATIO);
	shape.rotate(body->GetAngle() * DEGTORAD);

	window->draw(shape);
}