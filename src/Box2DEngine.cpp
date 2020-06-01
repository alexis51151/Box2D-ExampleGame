#include "Box2DEngine.h"
#include "Global.h"

sf::RenderWindow* Box2dEngine::app;
b2World* Box2dEngine::physicsWorld;

Box2dEngine::Box2dEngine(): resHeight(HEIGHT),resWidth(WIDTH)
{
}

Box2dEngine::Box2dEngine(int width, int height): resWidth(width) , resHeight(height) {
	sf::RenderWindow* temp = new sf::RenderWindow(sf::VideoMode(width, height), "My_word");
	temp->setFramerateLimit(60);
	temp->setVerticalSyncEnabled(true);
	Box2dEngine::app = temp;

	b2World* world = new b2World(b2Vec2(0.0f, 10.0f)); //gravity and sleep bodies
	Box2dEngine::physicsWorld = world;
}

Box2dEngine::~Box2dEngine()
{
}


b2Body* Box2dEngine::addStaticBox(int x, int y, float height, float width)
{
	// Define the ground body.
	b2BodyDef platformeBodyDef;
	platformeBodyDef.type = b2_staticBody;
	platformeBodyDef.position.Set(x*UNRATIO, y*UNRATIO);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = physicsWorld->CreateBody(&platformeBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(height * UNRATIO, width * UNRATIO);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
	return groundBody;
}
b2Body* Box2dEngine::addDynamicBox(int x, int y, float height, float width, Material material)
{
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	b2Body* body = physicsWorld->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(height * UNRATIO, width * UNRATIO);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = material.getDensity();
	fixtureDef.friction = material.getFriction();
	fixtureDef.restitution = material.getRestitution();
	

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
	return body;
}


