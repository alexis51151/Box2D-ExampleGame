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


	//create dynamic body
	myBodyDef.position.Set(x * UNRATIO, y * UNRATIO);
	b2Body* m_body = gameController->getPhysicsWorld()->CreateBody(&myBodyDef);

	//add main fixture
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	my_maindata = std::make_unique < FixtureData>(sf::Color::Green, Monstertype);
	playerFixture->SetUserData(static_cast<void*>(my_maindata.get()));

	//add foot sensor fixture
	b2PolygonShape LfootpolygonShape;
	LfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(-(width * UNRATIO),  height * UNRATIO), 0);
	b2FixtureDef LfootFixtureDef;
	LfootFixtureDef.isSensor = true;
	LfootFixtureDef.shape = &LfootpolygonShape;

	// filter
	LfootFixtureDef.filter.categoryBits = SENSOR;
	//LfootFixtureDef.filter.groupIndex = -10;
	LfootFixtureDef.filter.maskBits= PLATFORM;

	b2Fixture* LfootSensorFixture = m_body->CreateFixture(&LfootFixtureDef);
	Monster::my_Lfootdata = std::make_unique< FootData>(sf::Color::Green, MonsterLfoot);
	LfootSensorFixture->SetUserData(static_cast<void*>(my_Lfootdata.get()));

	//add foot sensor fixture
	b2PolygonShape RfootpolygonShape;
	RfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(width * UNRATIO, height * UNRATIO), 0);
	b2FixtureDef RfootFixtureDef;
	RfootFixtureDef.isSensor = true;
	RfootFixtureDef.shape = &RfootpolygonShape;

	//filter 
	RfootFixtureDef.filter.categoryBits = SENSOR;
	//RfootFixtureDef.filter.groupIndex = -10;
	RfootFixtureDef.filter.maskBits = PLATFORM;

	b2Fixture* RfootSensorFixture = m_body->CreateFixture(&RfootFixtureDef);
	Monster::my_Rfootdata = std::make_unique<FootData>(sf::Color::Green, MonsterRfoot);
	RfootSensorFixture->SetUserData(static_cast<void*>(my_Rfootdata.get()));

	//add triangular sensor for the player 
	
	const float radius = 6;
	const int nbpoint = 6;
	b2Vec2 vertices[nbpoint];
	b2Vec2 vertices2[nbpoint];
	const float min_angle = -10;
	const float max_angle = 10;
	float pas = (max_angle - min_angle)*2 / (nbpoint - 1);

	// Drawing the triangle
	vertices[0].Set(0, 0);
	vertices2[0].Set(0, 0);
	for (int i = 0; i < nbpoint-1 ; i++) {
		vertices[i + 1].Set(radius *cosf((i * pas + min_angle) * RADTODEG), -radius * sinf((i * pas + min_angle) * RADTODEG));
		vertices2[i + 1].Set(radius * -cosf((i * pas + min_angle) * RADTODEG), -radius * sinf((i * pas + min_angle) * RADTODEG));
	}

	b2PolygonShape coneShape;
	b2PolygonShape coneShape2;
	
	coneShape.Set(vertices, nbpoint);
	coneShape2.Set(vertices2, nbpoint);

	b2FixtureDef coneFixtures;
	b2FixtureDef coneFixtures2;

	coneFixtures.isSensor = true;
	coneFixtures2.isSensor = true;

	coneFixtures.shape = &coneShape;
	coneFixtures2.shape = &coneShape2;

	coneFixtures.filter.categoryBits = SENSOR;
	coneFixtures2.filter.categoryBits = SENSOR;

	coneFixtures.filter.groupIndex = -10;
	coneFixtures2.filter.groupIndex = -10;

	coneFixtures.filter.maskBits = PLAYER; // to only detect players 
	coneFixtures2.filter.maskBits = PLAYER;

	b2Fixture* coneSensorFixture = m_body->CreateFixture(&coneFixtures);
	b2Fixture* coneSensorFixture2 = m_body->CreateFixture(&coneFixtures2);

	Monster::my_Lviewdata = std::make_unique<ViewFieldData>(sf::Color::Green, viewField);
	Monster::my_Rviewdata = std::make_unique<ViewFieldData>(sf::Color::Green, viewField);

	my_Lviewdata->setDrawable(true);
	my_Rviewdata->setDrawable(true);

	coneSensorFixture->SetUserData(static_cast<void*>(my_Rviewdata.get()));
	coneSensorFixture2->SetUserData(static_cast<void*>(my_Lviewdata.get()));
	

	return m_body;
}

void Monster::updateSpeed()
{
	int lfootcontact = this->my_Lfootdata->GetNumFootContact();
	int rfootcontact = this->my_Rfootdata->GetNumFootContact();

	int Leftdetection = this->my_Lviewdata->getEntitidetected();
	int Rigdetection = this->my_Rviewdata->getEntitidetected();
	//si un joueur est detecter 
	bool playerdetected = (Leftdetection >= 1 && directionxsigne() == -1) || (Rigdetection >= 1 && directionxsigne() == 1);
	

	//affichage en fonction de la dirrection du deplacement 
	if (directionxsigne() == 1) {
		my_Rviewdata->setDrawable(true);
		my_Lviewdata->setDrawable(false);
	}
	else
	{
		my_Rviewdata->setDrawable(false);
		my_Lviewdata->setDrawable(true);
	}

	if (playerdetected) {
		timedetection++;
	}
	else{
		if(timedetection > 0) 
			timedetection--;
	}
	if (timedetection < 60){
		my_color = sf::Color::Blue;
	}
	else if (timedetection < 120) {
		my_color = sf::Color::Yellow;
	}
	else if (timedetection < 180) {
		my_color = sf::Color::Red;
	}
	if (rfootcontact >= 1 && lfootcontact >= 1) { //deux pieds aux sol 
		body->SetLinearVelocity(b2Vec2(this->directionxsigne()*5, 0));
		return;
	}
	if (lfootcontact < 1 && rfootcontact < 1){ //deux pieds en l'air 
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 10));
		return;
	}
	if (reverspeed_timout > 0)
		return;
	
	body->SetLinearVelocity(b2Vec2(-directionxsigne()*5, body->GetLinearVelocity().y));
	reverspeed_timout = 15;
}

void Monster::draw(sf::Color color, sf::RenderWindow* window) {
	for (auto& shape : shapes) {
		shape->draw(body, my_color, window);
	}
}