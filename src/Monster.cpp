#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(Box2DEngine* gameController, int x, int y, float height, float whidth)
{
	body = gameController->addBodyMonster(x, y, height, whidth );
	shape = std::unique_ptr<Rectangle>(new Rectangle());
}

FootData* Monster::getLeftfootData() {
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != nullptr) {
		FixtureData* userdata = static_cast<FixtureData*>( fixture->GetUserData() );
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
		FixtureData* userdata = static_cast<FixtureData*>(fixture->GetUserData());
		if (userdata->getDataType() == MonsterRfoot) {
			return (FootData*)userdata;
		}
		fixture = fixture->GetNext();
	}
	exit(1);
}

void Monster::updatespeed()
{
	int lfootcontact = this->getLeftfootData()->GetNumFootContact();
	int rfootcontact = this->getRightfootData()->GetNumFootContact();

	if (rfootcontact > 1 && lfootcontact > 1) { //deux pied aux sol 
		body->SetLinearVelocity(b2Vec2(this->directionxsigne()*10, 0));
		printf("sol \n");
		return;
	}
	if (lfootcontact < 1 && rfootcontact < 1){ //deux piid en l'air 
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 10));
		printf("air \n");
		return;
	}
	if (reverspeed_timout > 0)
		return;
	//on doit faire demitour 
	printf("revers speed \n");
	body->SetLinearVelocity(b2Vec2(-directionxsigne()*10, body->GetLinearVelocity().y));
	reverspeed_timout = 15;
}

void Monster::draw(sf::Color color, sf::RenderWindow* window) {
	shape->draw(body, color, window);
}