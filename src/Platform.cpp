#include "Platform.h"


Platform::Platform(Box2DEngine* gameController) {
	body = gameController->addStaticBox(10 * RATIO, 10 * RATIO, 5.0f * RATIO, 0.5f * RATIO);
	shape = std::unique_ptr<Shape>(new Rectangle());
}

void Platform::draw(sf::Color color, sf::RenderWindow* window) {
	shape->draw(body, color, window);
}