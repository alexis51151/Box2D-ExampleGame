#pragma once
#include "Box2DEngine.h"
#include "Global.h"
#include "Shape.h"
#include "Rectangle.h"
#include "ViewFieldData.h"
#include "Polygon.h"

class Monster
{
public:
	Monster();
	Monster(Box2DEngine* gameController, int x, int y, float width=1.0f*RATIO, float height=1.0f*RATIO);
	b2Body* getBody() const { return body; };
	void setBody(b2Body* val) { body = val; };
	int directionxsigne() { return (body->GetLinearVelocity().x > 0) ? 1 : -1; };
	void draw(sf::Color color, sf::RenderWindow* window);
	void updateSpeed();
	void decreaseReverseSpeedTimeout() { reverspeed_timout--; }
	b2Body* addBodyMonster(Box2DEngine* gameController, int x, int y, float height, float whidth);
	ViewFieldData* getMy_Lviewdata() const { return my_Lviewdata.get(); }
protected:

private:
	b2Body* body;
	int reverspeed_timout = 0;
	std::unique_ptr<FootData> my_Lfootdata;
	std::unique_ptr<FootData> my_Rfootdata;
	std::unique_ptr<FixtureData> my_maindata;
	std::unique_ptr<ViewFieldData> my_Lviewdata;
	std::unique_ptr<ViewFieldData> my_Rviewdata;
	std::vector<std::unique_ptr<Shape>> shapes;
	sf::Color my_color = sf::Color::Red;
	int timedetection = 0;
};
