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
	
	// Add the shape to the body and store the fixture address.
	b2Fixture* DynamicFixture = body->CreateFixture(&fixtureDef);
	// Add the Fixture data
	FixtureData* data = new FixtureData(sf::Color::Green, default);
	DynamicFixture->SetUserData(static_cast<void*>( data ));

	return body;
}
b2Body* Box2DEngine::addBodyMonster(int x, int y, float height, float width) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;

	//shape definition for main fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(height * UNRATIO, width * UNRATIO);

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	//create dynamic body
	myBodyDef.position.Set(x * UNRATIO, y * UNRATIO);
	b2Body* m_body = physicsWorld->CreateBody(&myBodyDef);
	
	//add main fixture
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	FixtureData* dataPlayer = new FixtureData(sf::Color::Green, Monstertype);
	playerFixture->SetUserData(static_cast<void*>( dataPlayer ));


	//add foot sensor fixture
	b2PolygonShape LfootpolygonShape;
	LfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(-(width * UNRATIO ), height * UNRATIO), 0);
	b2FixtureDef LfootFixtureDef;
	LfootFixtureDef.isSensor = true;
	LfootFixtureDef.shape = &LfootpolygonShape;
	b2Fixture* LfootSensorFixture = m_body->CreateFixture(&LfootFixtureDef);
	FootData* dataLFoot = new FootData(sf::Color::Green, MonsterLfoot);
	LfootSensorFixture->SetUserData(static_cast<void*>( dataLFoot ));

	//add foot sensor fixture
	b2PolygonShape RfootpolygonShape;
	RfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(width * UNRATIO , height * UNRATIO), 0);
	b2FixtureDef RfootFixtureDef;
	RfootFixtureDef.isSensor = true;
	RfootFixtureDef.shape = &RfootpolygonShape;
	b2Fixture* RfootSensorFixture = m_body->CreateFixture(&RfootFixtureDef);
	FootData* dataRFoot = new FootData(sf::Color::Green, MonsterRfoot);
	RfootSensorFixture->SetUserData(static_cast<void*>( dataRFoot ));

	return m_body;
}
b2Body* Box2DEngine::addBodyPlayer(int x, int y, float height, float width) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;
		
	//shape definition for main fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(width*UNRATIO, height*UNRATIO); 

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	//create dynamic body
	myBodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	b2Body* m_body = physicsWorld->CreateBody(&myBodyDef);

	//add main fixture
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	PlayerData* playerData = new PlayerData(sf::Color::Green, player, 0);
	playerFixture->SetUserData(static_cast<void*>( playerData ));

	
	//add foot sensor fixture
	b2PolygonShape footpolygonShape;
	footpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(0, height*UNRATIO), 0);
	b2FixtureDef footFixtureDef;
	footFixtureDef.isSensor = true;
	footFixtureDef.shape = &footpolygonShape;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&footFixtureDef);
	FootData * dataFoot = new FootData(sf::Color::Green, foot,0);
	footSensorFixture->SetUserData(static_cast<void*>( dataFoot ));

	//add hand sensor
	b2PolygonShape handpolygonShape;
	handpolygonShape.SetAsBox(width * UNRATIO+0.1,0.1 , b2Vec2(0, 0), 0);
	b2FixtureDef handfixture;
	handfixture.isSensor = true;
	handfixture.shape = &handpolygonShape;
	b2Fixture* handSensorFixture = m_body->CreateFixture(&handfixture);
	HandData* dataHand = new HandData(sf::Color::Green, hand,0);
	handSensorFixture->SetUserData(static_cast<void*>( dataHand ));
	

	//add triangular sensor for the player 

	const float radius = 8;
	const int nbpoint = 3;
	b2Vec2 vertices[nbpoint];
	const float min_angle = -45;
	const float max_angle = 45;
	float pas = (max_angle - min_angle) / (nbpoint - 1);
	vertices[0].Set(0, 0);
	for (int i = 0; i < nbpoint-1; i++) {
		vertices[i+1].Set(radius * cosf(i * pas*RADTODEG), -radius * sinf(i * pas* RADTODEG));
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

	b2Body* link = physicsWorld->CreateBody(&bodyDef);
	b2Fixture* Fixture = link->CreateFixture(&fixtureDef);
	FixtureData* data = new FixtureData(sf::Color::Cyan, rope);
	Fixture->SetUserData(static_cast<void*>( data ));

	elements.push_back(link);

	// Joint properties
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.localAnchorA.Set(width * UNRATIO, 0);
	revoluteJointDef.localAnchorB.Set(-width*UNRATIO, 0);

	for (int i = 1; i < nb_links; i++) {
		// Create a new body
		b2Body* newLink = physicsWorld->CreateBody(&bodyDef);
		// add userData
		b2Fixture* newFixture = newLink->CreateFixture(&fixtureDef);
		newFixture->SetUserData(static_cast<void*> ( data ));

		revoluteJointDef.bodyA = link;
		revoluteJointDef.bodyB = newLink;
		physicsWorld->CreateJoint(&revoluteJointDef);
		elements.push_back(newLink);

		link = newLink;

	}
	return elements;
}