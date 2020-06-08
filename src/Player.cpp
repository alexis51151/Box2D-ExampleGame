#include "Player.h"
#include "ViewFieldData.h"


b2Body* Player::addbodyplayer(Box2DEngine* gameController, int x, int y, float height, float width) {
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
	footFixtureDef.filter.maskBits = PLATFORM;

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


	return m_body;
}

Player::Player(Box2DEngine* gameController, int x, int y, float height, float width)
{
	Player::body = addbodyplayer(gameController,x , y, height , width );
	Player::shape = std::unique_ptr<Circle>(new Circle());
}

void Player::draw(sf::Color color, sf::RenderWindow* window) {
	Player::shape->draw(body, color, window);
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

