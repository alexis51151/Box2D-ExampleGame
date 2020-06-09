#pragma once
#include "Box2DEngine.h"
#include "Global.h"

#include "Circle.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Polygon.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include "ViewFieldData.h"

class Player
{
public:
	Player(Box2DEngine* gameController, int x = 40*RATIO, int y = 10*RATIO,float width = 1.f*RATIO, float height = 1.f * RATIO);
	b2Body* getBody() {return Player::body;};
	void draw(sf::Color color, sf::RenderWindow* window);
	void updatedirectionxsigne();
	void update();
	void actionLef();
	void actionRight();
	void actionDown();
	void actionUp();
	b2Body* addBodyPlayer(Box2DEngine* gameController, int x, int y, float width, float height);

private:
	b2Body* body;
	std::unique_ptr<HandData> my_handdata;
	std::unique_ptr<FootData> my_footdata;
	std::unique_ptr<PlayerData> my_playerdata;
	std::unique_ptr<ViewFieldData> my_Lviewdata;
	std::unique_ptr<ViewFieldData> my_Rviewdata;
	std::vector<std::unique_ptr<Shape>> shapes;
	int directionsigne = 1;
	bool playerdetected = false;
};