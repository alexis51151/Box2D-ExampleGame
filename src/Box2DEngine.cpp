#include "Box2DEngine.h"
#include "Global.h"

Box2DEngine::Box2DEngine(int width, int height) 
{
	Box2DEngine::app = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width, height), "My_word"));
	Box2DEngine::app->setFramerateLimit(60);
	Box2DEngine::app->setVerticalSyncEnabled(true);
	Box2DEngine::physicsWorld = std::unique_ptr<b2World>(new b2World(b2Vec2(0.0f, 10.0f)));
}

Box2DEngine::~Box2DEngine()
{
}

b2Body* Box2DEngine::addStaticBox(int x, int y, float width, float height)
{
	// Define the ground body.
	b2BodyDef platformeBodyDef;
	platformeBodyDef.type = b2_staticBody;
	platformeBodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	
	b2PolygonShape groundBox;
	groundBox.SetAsBox(width * UNRATIO, height * UNRATIO);
	// Define the ground box shape.
	
	b2FixtureDef my_fixture_def;
	my_fixture_def.shape = &groundBox;
	my_fixture_def.filter.categoryBits = PLATFORM;
	b2Body* groundBody = physicsWorld->CreateBody(&platformeBodyDef);


	// Add the ground fixture to the ground body.
	b2Fixture* staticFixture = groundBody->CreateFixture(&my_fixture_def);
	
	// Add the Fixture data
	FixtureData* data = new FixtureData(sf::Color::Red, platform);
	staticFixture->SetUserData(static_cast<void*>( data ));
	

	return groundBody;
}

b2Body* Box2DEngine::addDynamicBox(int x, int y, float height, float width, Material material)
{
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	//b2Body* body = physicsWorld->CreateBody(&bodyDef);
	b2Body* body = physicsWorld->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(width * UNRATIO, height * UNRATIO);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = material.getDensity();
	fixtureDef.friction = material.getFriction();
	fixtureDef.restitution = material.getRestitution();
	
	//filtre
	fixtureDef.filter.categoryBits = MOVING_OBJECT;
	fixtureDef.filter.groupIndex = default;

	// Add the shape to the body and store the fixture address.
	b2Fixture* DynamicFixture = body->CreateFixture(&fixtureDef);
	// Add the Fixture data (sans corp ) 
	FixtureData* data = new FixtureData(sf::Color::Green, default);
	DynamicFixture->SetUserData(static_cast<void*>( data ));
	
	return body;
}

