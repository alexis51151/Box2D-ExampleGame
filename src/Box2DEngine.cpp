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

b2Body* Box2DEngine::addStaticBox(int x, int y, float height, float width)
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
	b2Fixture* StaticFixture = groundBody->CreateFixture(&groundBox, 0.0f);
	
	// Add the Fixture data
	FixtureData* data = new FixtureData(sf::Color::Red, platform);
	StaticFixture->SetUserData(static_cast<void*>( data ));
	
	//add the filter 
	b2Filter temp;
	temp.categoryBits = PLATFORM;
	temp.groupIndex = platform;
	StaticFixture->SetFilterData(temp);

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
	dynamicBox.SetAsBox(height * UNRATIO, width * UNRATIO);

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

std::vector<b2Body*> Box2DEngine::addBodyRope(int x, int y, float length, int nb_links) {

	// Link width and height
	float width = length / nb_links;

	// Vector of bodies
	std::vector<b2Body*> elements;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(width * UNRATIO, width * UNRATIO);
	fixtureDef.shape = &polygonShape;

	//filter
	fixtureDef.filter.categoryBits = MOVING_OBJECT;
	fixtureDef.filter.groupIndex = default;

	b2Body* link = physicsWorld->CreateBody(&bodyDef);
	b2Fixture* Fixture = link->CreateFixture(&fixtureDef);
	FixtureData* data = new FixtureData(sf::Color::Cyan, rope);
	Fixture->SetUserData(static_cast<void*>( data ));

	elements.push_back(link);

	// Joint properties
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.localAnchorA.Set(width * UNRATIO, 0);
	revoluteJointDef.localAnchorB.Set(-width*UNRATIO, 0);
	//filtre 
	b2Filter link_filter;
	link_filter.categoryBits = MOVING_OBJECT;
	link_filter.groupIndex = default;

	for (int i = 1; i < nb_links; i++) {
		// Create a new body
		b2Body* newLink = physicsWorld->CreateBody(&bodyDef);
		// add userData
		b2Fixture* newFixture = newLink->CreateFixture(&fixtureDef);
		newFixture->SetUserData(static_cast<void*> ( data ));
		
		newFixture->SetFilterData(link_filter);

		revoluteJointDef.bodyA = link;
		revoluteJointDef.bodyB = newLink;
		physicsWorld->CreateJoint(&revoluteJointDef);
		elements.push_back(newLink);

		link = newLink;

	}
	return elements;
}