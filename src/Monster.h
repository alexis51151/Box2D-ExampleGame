#include "Box2DEngine.h"
#include "Global.h"
class Monster
{
public:
	Monster();
	Monster(Box2DEngine* gameController, int x, int y, float whidth=2.0f, float height=2.0f);
	b2Body* getBody() const { return body; };
	void setBody(b2Body* val) { body = val; };

	FootData* Monster::getRightfootData();
	FootData* Monster::getLeftfootData();

	void updatespeed();
	void decreace_reverspeed_timout() { reverspeed_timout--; }
protected:

private:
	b2Body* body;
	int reverspeed_timout = 0;
};
