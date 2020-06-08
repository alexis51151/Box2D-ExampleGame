#include "Monster.h"


Monster::Monster()
{
}

Monster::Monster(Box2DEngine* gameController, int x, int y, float height, float whidth)
{
	body = addBodyMonster(gameController, x, y, height, whidth);
	shapes.push_back(std::unique_ptr<Rectangle>(new Rectangle()));
	shapes.push_back(std::unique_ptr<Polygon>(new Polygon()));
}


b2Body* Monster::addBodyMonster(Box2DEngine* gameController, int x, int y, float height, float width) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;

	//shape definition for main fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(height * UNRATIO, width * UNRATIO);

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	// filter 
	myFixtureDef.filter.categoryBits = MONSTER;
	myFixtureDef.filter.groupIndex = Monstertype;

	//create dynamic body
	myBodyDef.position.Set(x * UNRATIO, y * UNRATIO);
	b2Body* m_body = gameController->getPhysicsWorld()->CreateBody(&myBodyDef);

	//add main fixture
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	Monster::my_maindata = std::make_unique < FixtureData>(sf::Color::Green, Monstertype);
	playerFixture->SetUserData(static_cast<void*>(my_maindata.get()));

	//add foot sensor fixture
	b2PolygonShape LfootpolygonShape;
	LfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2( height * UNRATIO, -(width * UNRATIO)), 0);
	b2FixtureDef LfootFixtureDef;
	LfootFixtureDef.isSensor = true;
	LfootFixtureDef.shape = &LfootpolygonShape;

	// filter
	LfootFixtureDef.filter.categoryBits = SENSOR;
	LfootFixtureDef.filter.groupIndex = MonsterLfoot;
	LfootFixtureDef.filter.maskBits= PLATFORM;

	b2Fixture* LfootSensorFixture = m_body->CreateFixture(&LfootFixtureDef);
	Monster::my_Lfootdata = std::make_unique< FootData>(sf::Color::Green, MonsterLfoot);
	LfootSensorFixture->SetUserData(static_cast<void*>(my_Lfootdata.get()));
	LfootFixtureDef.filter.maskBits = PLATFORM;
	//add foot sensor fixture
	b2PolygonShape RfootpolygonShape;
	RfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(height * UNRATIO,width * UNRATIO), 0);
	b2FixtureDef RfootFixtureDef;
	RfootFixtureDef.isSensor = true;
	RfootFixtureDef.shape = &RfootpolygonShape;

	//filter 
	RfootFixtureDef.filter.categoryBits = SENSOR;
	RfootFixtureDef.filter.groupIndex = MonsterRfoot;
	RfootFixtureDef.filter.maskBits = PLATFORM;

	b2Fixture* RfootSensorFixture = m_body->CreateFixture(&RfootFixtureDef);
	Monster::my_Rfootdata = std::make_unique<FootData>(sf::Color::Green, MonsterRfoot);
	RfootSensorFixture->SetUserData(static_cast<void*>(my_Rfootdata.get()));

	//add triangular sensor for the player 
	const float radius = 3;
	const int nbpoint = 3;
	b2Vec2 vertices[nbpoint];
	const float min_angle = -10;
	const float max_angle = 30;
	float pas = (max_angle - min_angle)*2 / (nbpoint - 1);

	// Drawing the triangle
	vertices[0].Set(0, 0);
	for (int i = 0; i < nbpoint-1 ; i++) {
		vertices[i + 1].Set(radius *- cosf((i * pas + min_angle) * RADTODEG), -radius * sinf((i * pas + min_angle) * RADTODEG));
	}

	b2PolygonShape coneShape;
	coneShape.Set(vertices, nbpoint);
	myFixtureDef.shape = &polygonShape;
	b2FixtureDef coneFixtures;
	coneFixtures.isSensor = true;
	coneFixtures.shape = &coneShape;

	coneFixtures.filter.categoryBits = SENSOR;
	coneFixtures.filter.maskBits = PLAYER; // to only detect players 

	b2Fixture* coneSensorFixture = m_body->CreateFixture(&coneFixtures);
	Monster::my_Rviewdata = std::make_unique<ViewFieldData>(sf::Color::Green, viewField);
	my_Rviewdata->setDrawable(true);
	coneSensorFixture->SetUserData(static_cast<void*>(my_Rviewdata.get()));

	return m_body;
}


void Monster::updateSpeed()
{
	int lfootcontact = this->my_Lfootdata->GetNumFootContact();
	int rfootcontact = this->my_Rfootdata->GetNumFootContact();

	if (rfootcontact > 1 && lfootcontact > 1) { //deux pieds aux sol 
		body->SetLinearVelocity(b2Vec2(this->directionxsigne()*5, 0));
		return;
	}
	if (lfootcontact < 1 && rfootcontact < 1){ //deux pieds en l'air 
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 10));
		return;
	}
	if (reverspeed_timout > 0)
		return;
	//on doit faire demi-tour 
	printf("revers speed \n");
	body->SetLinearVelocity(b2Vec2(-directionxsigne()*5, body->GetLinearVelocity().y));
	reverspeed_timout = 15;
}

void Monster::draw(sf::Color color, sf::RenderWindow* window) {
	for (auto& shape : shapes) {
		shape->draw(body, color, window);
	}
}