#include "Player.h"
#include "Rectangle.h"


Player::Player(Box2DEngine* gameController)
{
	Player::body = gameController->addBodyPlayer(10 * RATIO, 10 * RATIO, 1.0f * RATIO, 1.0f * RATIO);
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

