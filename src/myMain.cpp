#include "myMain.h"

int numFootContact = 0;  // =0 a ajouter a un constructeur de jeu 


int myMain() {
	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	b2Body* player = gameController.addBodyPlayer(10 * RATIO , 10 * RATIO , 1.0f * RATIO, 1.0f * RATIO);

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	// Player shape
	sf::CircleShape c(1.0f*RATIO);
	c.setFillColor(sf::Color::Green);
	// Platform shape
	sf::RectangleShape r(sf::Vector2f(8.0f*2*RATIO, 1.0f*2*RATIO)); // *2 because box2D takes mid-height and mid-width 
	r.setFillColor(sf::Color::Red);

	while (window->isOpen())
	{
		// Events.cpp : handle mouse and keyboard events
		HookEvents(window, &gameController, player);
	
		window->clear(sf::Color::White);
		world->Step(timeStep, velocityIterations, positionIterations);
		for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				// Draw.cpp : draw box2D fixtures with SFML
				
				if (numFootContact >= 1) {
					c.setFillColor(sf::Color::Blue);
				}
				else {
					c.setFillColor(sf::Color::Green);
				}
				
				DrawShape(BodyIterator, &c, window);
			}
			if (BodyIterator->GetType() == b2_staticBody)
			{
				DrawShape(BodyIterator, &r, window);
			}
		}
		window->display();
	}
	return 0;
}

