#include "Player.h"
#include "Rectangle.h"


b2Body* addbodyplayer(Box2DEngine* gameController, int x, int y, float height, float width) {
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
	myFixtureDef.filter.groupIndex = player;

	//create dynamic body
	myBodyDef.position.Set(x * UNRATIO, y * UNRATIO);
	b2Body* m_body = gameController->getPhysicsWorld()->CreateBody(&myBodyDef);

	//add main fixture
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	PlayerData* playerData = new PlayerData(sf::Color::Green, player, 0);
	playerFixture->SetUserData(static_cast<void*>(playerData));


	//add foot sensor fixture
	b2PolygonShape footpolygonShape;
	footpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(0, height * UNRATIO), 0);
	b2FixtureDef footFixtureDef;
	footFixtureDef.isSensor = true;
	footFixtureDef.shape = &footpolygonShape;

	//filter
	footFixtureDef.filter.categoryBits = SENSOR;
	footFixtureDef.filter.groupIndex = foot;

	b2Fixture* footSensorFixture = m_body->CreateFixture(&footFixtureDef);
	FootData* dataFoot = new FootData(sf::Color::Green, foot, 0);
	footSensorFixture->SetUserData(static_cast<void*>(dataFoot));

	//add hand sensor
	b2PolygonShape handpolygonShape;
	handpolygonShape.SetAsBox(width * UNRATIO + 0.1, 0.1, b2Vec2(0, 0), 0);
	b2FixtureDef handfixture;
	handfixture.isSensor = true;
	handfixture.shape = &handpolygonShape;

	//filter
	footFixtureDef.filter.categoryBits = SENSOR;
	footFixtureDef.filter.groupIndex = hand;

	b2Fixture* handSensorFixture = m_body->CreateFixture(&handfixture);
	HandData* dataHand = new HandData(sf::Color::Green, hand, 0);
	handSensorFixture->SetUserData(static_cast<void*>(dataHand));

	//add triangular sensor for the player 

	const float radius = 8;
	const int nbpoint = 3;
	b2Vec2 vertices[nbpoint];
	const float min_angle = -45;
	const float max_angle = 45;
	float pas = (max_angle - min_angle) / (nbpoint - 1);
	vertices[0].Set(0, 0);
	for (int i = 0; i < nbpoint - 1; i++) {
		vertices[i + 1].Set(radius * cosf(i * pas * RADTODEG), -radius * sinf(i * pas * RADTODEG));
	}
	b2PolygonShape coneshape;
	coneshape.Set(vertices, nbpoint);
	myFixtureDef.shape = &polygonShape;
	b2FixtureDef conefixtures;
	conefixtures.isSensor = true;
	conefixtures.shape = &coneshape;
	//b2Fixture* conseSensorFixture = m_body->CreateFixture(&conefixtures);
	FixtureData* consefixturedata = new FixtureData(sf::Color::Green, default);
	//conseSensorFixture->SetUserData(static_cast<void*>(consefixturedata));

	return m_body;
}

Player::Player(Box2DEngine* gameController)
{
	Player::body = addbodyplayer(gameController,10 * RATIO, 10 * RATIO, 1.0f * RATIO, 1.0f * RATIO);
	Player::shape = std::unique_ptr<Circle>(new Circle());
}

void Player::draw(sf::Color color, sf::RenderWindow* window) {
	Player::shape->draw(body, color, window);
}

void Player::actionLef()
{
	int footcount;
	int handcount;
	int jumptimout;
	getvalue(body, &footcount, &handcount, &jumptimout);

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
	int footcount;
	int handcount;
	int jumptimout;
	getvalue(body, &footcount, &handcount, &jumptimout);

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
	PlayerData* playerdata;
	FootData* footData;
	HandData* handData;
	b2Fixture* playerfixtures = body->GetFixtureList();
	while (playerfixtures != nullptr) {
		FixtureData* userdata = static_cast<FixtureData*>(playerfixtures->GetUserData());
		int datatype = userdata->getDataType();
		switch (datatype)
		{
		case player:
			playerdata = ((PlayerData*)userdata);
			break;
		case foot:
			footData = ((FootData*)userdata);
			break;
		case hand:
			handData = ((HandData*)userdata);
			break;
		default:
			printf("attention type de features non prisent en compte ");
			break;
		}
		playerfixtures = playerfixtures->GetNext();
	}

	if (footData == nullptr || handData == nullptr || playerdata == nullptr) {
		printf("erreur dans la recuperation");
		exit(1);
	}

	if (footData->GetNumFootContact() < 1 && handData->GetNumhandContact() < 1) {
		return;

	}
	if (playerdata->GetJumpTimeout() > 0) return;
	body->ApplyLinearImpulseToCenter(b2Vec2(0, -body->GetMass() * 10), true);
	playerdata->SetJumpTimeout(15);
}

