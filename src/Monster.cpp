#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(Box2DEngine* gameController, int x, int y, float height, float whidth)
{
	body=gameController->addBodyMonster(x * RATIO, y * RATIO, height * RATIO, whidth * RATIO );
}

FootData* Monster::getLeftfootData() {
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != nullptr) {
		FixtureData* userdata = ((FixtureData*)fixture->GetUserData());
		int datatype = userdata->getDataType();
		if (datatype = MonsterLfoot) {
			return (FootData*)userdata;
		}
	}
}
FootData* Monster::getRightfootData() {
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != nullptr) {
		FixtureData* userdata = ((FixtureData*)fixture->GetUserData());
		int datatype = userdata->getDataType();
		if (datatype = MonsterRfoot) {
			return (FootData*)userdata;
		}
	}
}

void Monster::updatespeed()
{
	if (getRightfootData()->GetNumFootContact() > 1 && getLeftfootData()->GetNumFootContact() > 1) //deux pied aux sol
		return;
	if (reverspeed_timout > 0)
		return;
	body->SetLinearVelocity(-body->GetLinearVelocity());
}
