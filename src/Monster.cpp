#include "Monster.h"


Monster::Monster()
{
}

Monster::Monster(Box2DEngine* gameController, int x, int y, float height, float whidth)
{
	body=gameController->addBodyMonster(x * RATIO, y * RATIO, height * RATIO, whidth * RATIO );
}
FootData* getLeftfootData() {
	b2Fixture* fixture = b2Body->GetFixtureList();
	while (fixture != nullptr) {
		FixtureData* userdata = ((FixtureData*)playerfixtures->GetUserData());
		int datatype = userdata->getDataType();
		if (datatype = MonsterLfoot) {
			return (FootData*)userdata;
		}
	}
}
FootData* getRightfootData() {
	b2Fixture* fixture = b2Body->GetFixtureList();
	while (fixture != nullptr) {
		FixtureData* userdata = ((FixtureData*)playerfixtures->GetUserData());
		int datatype = userdata->getDataType();
		if (datatype = MonsterRfoot) {
			return (FootData*)userdata;
		}
	}
}

void Monster::updatespeed()
{
	if (getRightfootData() > 1 && getLeftfootData() > 1) //deux pied aux sol
		return;
	if (reverspeed_timout > 0)
		return;
	body->SetLinearVelocity(- body->GetLinearVelocity() )
}
