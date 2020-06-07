#include "Monster.h"

Monster::Monster()
{
}

b2Body* addBodyMonster(Box2DEngine* gameController, int x, int y, float height, float whidth) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;

	//shape definition for main fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(height * UNRATIO, whidth * UNRATIO);

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
	//ajout du filtre 
	myFixtureDef.filter.categoryBits = MONSTER;
	myFixtureDef.filter.groupIndex = Monstertype;

	//create dynamic body
	myBodyDef.position.Set(x * UNRATIO, y * UNRATIO);
	b2Body* m_body = gameController->getPhysicsWorld()->CreateBody(&myBodyDef);

	//add main fixture
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	FixtureData* dataPlayer = new FixtureData(sf::Color::Green, Monstertype);
	playerFixture->SetUserData(static_cast<void*>(dataPlayer));

	//add foot sensor fixture
	b2PolygonShape LfootpolygonShape;
	LfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(-(whidth * UNRATIO), height * UNRATIO), 0);
	b2FixtureDef LfootFixtureDef;
	LfootFixtureDef.isSensor = true;
	LfootFixtureDef.shape = &LfootpolygonShape;

	//filtre
	LfootFixtureDef.filter.categoryBits = SENSOR;
	LfootFixtureDef.filter.groupIndex = MonsterLfoot;

	b2Fixture* LfootSensorFixture = m_body->CreateFixture(&LfootFixtureDef);
	FootData* dataLFoot = new FootData(sf::Color::Green, MonsterLfoot);
	LfootSensorFixture->SetUserData(static_cast<void*>(dataLFoot));

	//add foot sensor fixture
	b2PolygonShape RfootpolygonShape;
	RfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(whidth * UNRATIO, height * UNRATIO), 0);
	b2FixtureDef RfootFixtureDef;
	RfootFixtureDef.isSensor = true;
	RfootFixtureDef.shape = &RfootpolygonShape;

	//filter 
	RfootFixtureDef.filter.categoryBits = SENSOR;
	RfootFixtureDef.filter.groupIndex = MonsterRfoot;

	b2Fixture* RfootSensorFixture = m_body->CreateFixture(&RfootFixtureDef);
	FootData* dataRFoot = new FootData(sf::Color::Green, MonsterRfoot);
	RfootSensorFixture->SetUserData(static_cast<void*>(dataRFoot));

	return m_body;
}

Monster::Monster(Box2DEngine* gameController, int x, int y, float height, float whidth)
{
	body = addBodyMonster(gameController, x, y, height, whidth);
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