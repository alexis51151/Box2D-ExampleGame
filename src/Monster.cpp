#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(Box2DEngine* gameController, int x, int y, float height, float whidth)
{
	body=gameController->addBodyMonster(x, y, height, whidth );
}

FootData* Monster::getLeftfootData() {
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != nullptr) {
		FixtureData* userdata = ((FixtureData*)fixture->GetUserData());
		if (userdata->getDataType()== MonsterLfoot) {
			return (FootData*)userdata;
		}
		fixture = fixture->GetNext();
	}
	exit(1);
}
FootData* Monster::getRightfootData() {
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != nullptr) {
		FixtureData* userdata = ((FixtureData*)fixture->GetUserData());
		if (userdata->getDataType() == MonsterRfoot) {
			return (FootData*)userdata;
		}
		fixture = fixture->GetNext();
	}

}

void Monster::updatespeed()
{
	int lfootcontact = this->getLeftfootData()->GetNumFootContact();
	int rfootcontact = this->getRightfootData()->GetNumFootContact();
	printf("lf : %d , rf: %d \n", lfootcontact, rfootcontact);
	if (rfootcontact > 1 && lfootcontact > 1) { //deux pied aux sol 
		return;
	}
	if (lfootcontact < 1 && rfootcontact < 1){ //deux piid en l'air 
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 10));
		return;
	}
	if (reverspeed_timout > 0)
		return;
	printf("lf : %d , rf: %d \n", lfootcontact,rfootcontact);
	printf("inversion vitess\n",rfootcontact);
	body->SetLinearVelocity(b2Vec2(-body->GetLinearVelocity().x, body->GetLinearVelocity().y));
	reverspeed_timout = 15;
}
