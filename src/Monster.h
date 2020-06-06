#include "Box2DEngine.h"
#include "Global.h"
#include "Shape.h"
#include "Rectangle.h"

class Monster
{
public:
	Monster();
	Monster(Box2DEngine* gameController, int x, int y, float width=1.0f*RATIO, float height=1.0f*RATIO);
	b2Body* getBody() const { return body; };
	void setBody(b2Body* val) { body = val; };
	int directionxsigne() { return (body->GetLinearVelocity().x > 0) ? 1 : -1; };
	FootData* Monster::getRightfootData();
	FootData* Monster::getLeftfootData();
	void draw(sf::Color color, sf::RenderWindow window);
	void updatespeed();
	void decreace_reverspeed_timout() { reverspeed_timout--; }
protected:

private:
	b2Body* body;
	int reverspeed_timout = 0;
	std::unique_ptr<Shape> shape;
};
