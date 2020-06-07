#include "Platform.h"


Platform::Platform(Box2DEngine* gameController, int x, int y, float height, float width) {
	body = gameController->addStaticBox(x, y, height, width);
	shape = std::unique_ptr<Rectangle>(new Rectangle());
}

void Platform::draw(sf::Color color, sf::RenderWindow* window) {
	shape->draw(body, color, window);
}