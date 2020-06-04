#include <Events.h>
#include "myMain.h"

void HookEvents(sf::Window* window, Box2DEngine* gameController, b2Body* player) {
	sf::Event event;
	float impulse = player->GetMass() * 10;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			float MouseX = sf::Mouse::getPosition(*window).x;
			float MouseY = sf::Mouse::getPosition(*window).y;
			gameController->addDynamicBox(MouseX, MouseY, 1.0f * RATIO, 1.0f * RATIO, Material::WOOD);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			float MouseX = sf::Mouse::getPosition(*window).x;
			float MouseY = sf::Mouse::getPosition(*window).y;
			gameController->addStaticBox(MouseX, MouseY, 8.0f * RATIO, 1.0f * RATIO);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			actionplayerLeftKey(player);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			actionplayerRightKey(player);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			actionplayerDownKey(player);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			actionplayerUpKey(player);
		}
	}
}


void actionplayerRightKey(b2Body* player)
{
	int footcount;
	int handcount;
	int jumptimout;
	getvalue(player, &footcount, &handcount, &jumptimout);

	if (footcount < 1 && handcount < 1 && jumptimout > 0) { //enlair 
		if (player->GetLinearVelocity().x >= 5) {
			player->SetLinearVelocity(b2Vec2(10, player->GetLinearVelocity().y));
		}
		else
		{
			player->ApplyLinearImpulseToCenter(b2Vec2(10, 0), true);
		}

	}else{
		if (player->GetLinearVelocity().x >= 10) {
			player->SetLinearVelocity(b2Vec2(20, player->GetLinearVelocity().y));
		}
		else
		{
			player->ApplyLinearImpulseToCenter(b2Vec2(20, 0), true);
		}
	}
}

void actionplayerLeftKey(b2Body* player)
{
	int footcount;
	int handcount;
	int jumptimout;
	getvalue(player, &footcount, &handcount, &jumptimout);

	PlayerData* playerdata = (PlayerData*)player->GetUserData();
	if (footcount < 1 && handcount < 1 && jumptimout > 0) { //enlair
		if (player->GetLinearVelocity().x <= -5) {
			player->SetLinearVelocity(b2Vec2(-10, player->GetLinearVelocity().y));
		}
		else
		{
			player->ApplyLinearImpulseToCenter(b2Vec2(-10, 0), true);
		}

	}
	else {
		if (player->GetLinearVelocity().x <= -10) {
			player->SetLinearVelocity(b2Vec2(-20, player->GetLinearVelocity().y));
		}
		else
		{
			player->ApplyLinearImpulseToCenter(b2Vec2(-20, 0), true);
		}
	}
}

void actionplayerDownKey(b2Body* player)
{
	//nothingtodo
}

void actionplayerUpKey(b2Body* player1)
{
	PlayerData* playerdata;
	FootData* footData;
	HandData* handData;
	b2Fixture* playerfixtures = player1->GetFixtureList();
	while (playerfixtures != nullptr) {
		FixtureData* userdata = ((FixtureData*)playerfixtures->GetUserData());
		int datatype = userdata->getDataType();
		switch (datatype)
		{
		case player:
			playerdata = ((PlayerData*)userdata);
			break;
		case foot:
			footData= ((FootData*)userdata);
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
	if (footData == nullptr || handData == nullptr)
		printf("erreur dans la recuperation");
	if (footData->GetNumFootContact() < 1 && handData->GetNumhandContact()<1 ) {
		return;
	}
	printf("jumptimout %d", playerdata->GetJumpTimeout());
	if (playerdata->GetJumpTimeout() > 0) return;
	player1->ApplyLinearImpulseToCenter(b2Vec2(0, -player1->GetMass() * 10), true);
	playerdata->SetJumpTimeout(15);
	
}
