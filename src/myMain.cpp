#include "myMain.h"

int numFootContact = 0;  // =0 a ajouter a un constructeur de jeu 
int numhandContact = 0;

int m_jumpTimeout;

int myMain() {
	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	std::unique_ptr<Player> player(new Player(&gameController));
	b2Body* player_body = player->getBody();

	std::unique_ptr<Rope> rope(new Rope(800,400, 3.0 * RATIO, 2, &gameController));


	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	while (window->isOpen())
	{
		// Events.cpp : handle mouse and keyboard events
		HookEvents(window, &gameController, player_body);
	
		window->clear(sf::Color::White);
		m_jumpTimeout--;
		world->Step(timeStep, velocityIterations, positionIterations);
		for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				// Draw.cpp : draw box2D fixtures with SFML
				sf::Color color = sf::Color::Green;
				if (numFootContact >= 1) {
					color = sf::Color::Blue;
				}else{
					if (numhandContact >= 1) {
						color = sf::Color::Red;
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

