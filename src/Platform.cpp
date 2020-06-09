#include "Platform.h"


Platform::Platform(Box2DEngine* gameController, int x, int y,float width, float height) {
	body = gameController->addStaticBox(x, y, width, height);
	shape = std::unique_ptr<Rectangle>(new Rectangle());
}

void Platform::draw(sf::Color color, sf::RenderWindow* window) {
	shape->draw(getBody(), color, window);
}