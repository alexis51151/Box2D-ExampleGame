#include "myMain.h"

int myMain() {
	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	std::unique_ptr<Player> player1(new Player(&gameController));
	std::unique_ptr<Player> player2(new Player(&gameController));
	b2Body* player1_body = player1->getBody();
	b2Body* player2_body = player2->getBody();

	// Link the two players with a rope
	std::unique_ptr<Rope> rope(new Rope(800,400, 10 * RATIO, 30, &gameController));
	rope->linkPlayers(player1.get(), player2.get(), world);

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	while (window->isOpen())
	{
		// Events.cpp : handle mouse and keyboard events
		HookEvents(window, &gameController, player1_body);
	
		window->clear(sf::Color::White);

		getPlayerData(player1_body)->decreaseJumpTimeout();
		getPlayerData(player2_body)->decreaseJumpTimeout();



		world->Step(timeStep, velocityIterations, positionIterations);
		for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{	
				sf::Color color = sf::Color::Green;
				if (((FixtureData*)BodyIterator->GetFixtureList()->GetUserData() != nullptr && ((FixtureData*)BodyIterator->GetFixtureList()->GetUserData())->getDataType()==player)) {
					// Draw.cpp : draw box2D fixtures with SFML
					int footcount;
					int handcount;
					int jumptimout;
					getvalue(BodyIterator, &footcount, &handcount, &jumptimout);
					if (footcount >= 1) {
						color = sf::Color::Blue;
					}
					else {
						if (handcount >= 1) {
							color = sf::Color::Red;
						}
					}
				}
				DrawShape(BodyIterator, color, window);
			}
			if (BodyIterator->GetType() == b2_staticBody)
			{
				DrawShape(BodyIterator, sf::Color::Red, window);
			}
		}
		window->display();
	}
	return 0;
}

