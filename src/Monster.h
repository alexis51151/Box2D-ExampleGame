#include "Box2DEngine.h"
#include "Global.h"
class Monster
{
public:
	Monster();
	Monster(Box2DEngine* gameController, int x, int y, float whidth=2.0f, float height=2.0f);
	b2Body* getBody() const { return body; }
	void setBody(b2Body* val) { body = val; }
protected:

private:
	b2Body* body;
};
