#include "Circle.h"

Circle::Circle() {
}

void Circle::draw(b2Body* body, sf::Color color, sf::RenderWindow* window) {
	std::pair<float, float> dimensions = getBodyDimensions(body);
	float radius = dimensions.first;
	
	b2Vec2 position = body->GetPosition();

	sf::CircleShape shape(radius / 2 * RATIO);
	shape.setFillColor(color);

	
	// Setting position and drawing with SFML
	shape.setPosition((position.x - radius / 2) * RATIO, (position.y - radius / 2) * RATIO);
	shape.rotate(body->GetAngle() * RADTODEG);

	window->draw(shape);
}