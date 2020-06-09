#include "Player.h"



b2Body* Player::addBodyPlayer(Box2DEngine* gameController, int x, int y, float height, float width) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;

	//shape definition for main fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(width * UNRATIO, height * UNRATIO);

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	//filter
	myFixtureDef.filter.categoryBits = PLAYER;

	//create dynamic body
	myBodyDef.position.Set(x * UNRATIO, y * UNRATIO);
	b2Body* m_body = gameController->getPhysicsWorld()->CreateBody(&myBodyDef);

	//add main fixture
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	Player::my_playerdata= std::make_unique<PlayerData>(sf::Color::Green, player, 0);
	playerFixture->SetUserData(static_cast<void*>(my_playerdata.get()));

	//add foot sensor fixture
	b2PolygonShape footpolygonShape;
	footpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(0, height * UNRATIO), 0);
	b2FixtureDef footFixtureDef;
	footFixtureDef.isSensor = true;
	footFixtureDef.shape = &footpolygonShape;

	//filter
	footFixtureDef.filter.categoryBits = SENSOR;
	footFixtureDef.filter.maskBits = PLATFORM| MOVING_OBJECT;

	b2Fixture* footSensorFixture = m_body->CreateFixture(&footFixtureDef);
	my_footdata = std::make_unique<FootData>(sf::Color::Green, foot, 0);
	footSensorFixture->SetUserData(static_cast<void*>(my_footdata.get()));
	
	//add hand sensor
	b2PolygonShape handpolygonShape;
	handpolygonShape.SetAsBox(width * UNRATIO + 0.1, 0.1, b2Vec2(0, 0), 0);
	b2FixtureDef handfixture;
	handfixture.isSensor = true;
	handfixture.shape = &handpolygonShape;

	//filter
	handfixture.filter.categoryBits = SENSOR;
	handfixture.filter.maskBits = PLATFORM;

	b2Fixture* handSensorFixture = m_body->CreateFixture(&handfixture);
	my_handdata= std::make_unique<HandData>(sf::Color::Green, hand, 0);
	handSensorFixture->SetUserData(static_cast<void*>(my_handdata.get()));
	
	const float radius = 6;
	const int nbpoint = 6;
	b2Vec2 vertices[nbpoint];
	b2Vec2 vertices2[nbpoint];
	const float min_angle = -10;
	const float max_angle = 10;
	float pas = (max_angle - min_angle) * 2 / (nbpoint - 1);

	// Drawing the triangle
	vertices[0].Set(0, 0);
	vertices2[0].Set(0, 0);
	for (int i = 0; i < nbpoint - 1; i++) {
		vertices[i + 1].Set(radius * cosf((i * pas + min_angle) * RADTODEG), -radius * sinf((i * pas + min_angle) * RADTODEG));
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

	Player::my_Lviewdata = std::make_unique<ViewFieldData>(sf::Color::Green, viewField);
	Player::my_Rviewdata = std::make_unique<ViewFieldData>(sf::Color::Green, viewField);

	my_Lviewdata->setDrawable(true);
	my_Rviewdata->setDrawable(true);

	coneSensorFixture->SetUserData(static_cast<void*>(my_Rviewdata.get()));
	coneSensorFixture2->SetUserData(static_cast<void*>(my_Lviewdata.get()));

	return m_body;
}



Player::Player(Box2DEngine * gameController, int x, int y, float height, float width) {
	Player::body = addBodyPlayer(gameController, x, y, height, width);
	Player::shapes.push_back(std::unique_ptr<Circle>(new Circle()));
	Player::shapes.push_back(std::unique_ptr<Polygon>(new Polygon()));
}


void Player::draw(sf::Color color, sf::RenderWindow* window) {
	update();
	for (auto& shape : shapes) {
		shape->draw(body, color, window);
	}
}

void Player::updatedirectionxsigne()
{
	float xvelocity = body->GetLinearVelocity().x;
	if (xvelocity > 0) {
		directionsigne = 1;
	}
	else if (xvelocity < 0) {
		directionsigne = -1;
	}
	// si non on garde la meme valeur evite de trop changer 
}

void Player::update()
{
	updatedirectionxsigne();
	if (directionsigne == 1) {
		my_Lviewdata->setDrawable(false);
		my_Rviewdata->setDrawable(true);
	}
	else
	{
		my_Lviewdata->setDrawable(true);
		my_Rviewdata->setDrawable(false);
	}
	playerdetected = (my_Rviewdata->getEntitidetected() >= 1 && directionsigne == 1)
					|| (my_Lviewdata->getEntitidetected() >= 1 && directionsigne == -1);
	if (playerdetected) {
		printf("joueur detecter  \n");
	}

}

void Player::actionLef()
{
	int footcount = my_footdata->GetNumFootContact();
	int handcount=my_handdata->GetNumhandContact();
	int jumptimout = my_playerdata->GetJumpTimeout();
	PlayerData* playerdata = (PlayerData*)body->GetUserData();
	if (footcount < 1 && handcount < 1 && jumptimout > 0) { //enlair
		if (body->GetLinearVelocity().x <= -5) {
			body->SetLinearVelocity(b2Vec2(-10, body->GetLinearVelocity().y));
		}
		else
		{
			body->ApplyLinearImpulseToCenter(b2Vec2(-10, 0), true);
		}
	}
	else {
		if (body->GetLinearVelocity().x <= -10) {
			body->SetLinearVelocity(b2Vec2(-20, body->GetLinearVelocity().y));
		}
		else
		{
			body->ApplyLinearImpulseToCenter(b2Vec2(-20, 0), true);
		}
	}
}

void Player::actionRight()
{

	int footcount = my_footdata->GetNumFootContact();
	int handcount = my_handdata->GetNumhandContact();
	int jumptimout = my_playerdata->GetJumpTimeout();
	

	if (footcount < 1 && handcount < 1 && jumptimout > 0) { //enlair 
		if (body->GetLinearVelocity().x >= 5) {
			body->SetLinearVelocity(b2Vec2(10, body->GetLinearVelocity().y));
		}
		else
		{
			body->ApplyLinearImpulseToCenter(b2Vec2(10, 0), true);
		}

	}
	else {
		if (body->GetLinearVelocity().x >= 10) {
			body->SetLinearVelocity(b2Vec2(20, body->GetLinearVelocity().y));
		}
		else
		{
			body->ApplyLinearImpulseToCenter(b2Vec2(20, 0), true);
		}
	}
}

void Player::actionDown()
{
	//nothing yet 
}

void Player::actionUp()
{
	
	if (my_footdata->GetNumFootContact() < 1 && my_handdata->GetNumhandContact() < 1) {
		return;

	}
	if (my_playerdata->GetJumpTimeout() > 0) return;
	body->ApplyLinearImpulseToCenter(b2Vec2(0, -body->GetMass() * 30), true);
	my_playerdata->SetJumpTimeout(15);
}

