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
	//b2Body* groundBody = physicsWorld->CreateBody(&platformeBodyDef);
	b2Body* groundBody = physicsWorld->CreateBody(&platformeBodyDef);
	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(height * UNRATIO, width * UNRATIO);

	// Add the ground fixture to the ground body.
	b2Fixture* StaticFixture = groundBody->CreateFixture(&groundBox, 0.0f);
	// Add the Fixture data
	FixtureData* data = new FixtureData(sf::Color::Red, platform);
	StaticFixture->SetUserData((void*)data);

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
	DynamicFixture->SetUserData((void*)data);

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
	m_body->CreateFixture(&myFixtureDef);
	b2Fixture* playerFixture = m_body->CreateFixture(&myFixtureDef);
	FixtureData* dataPlayer = new FixtureData(sf::Color::Green, player);
	playerFixture->SetUserData((void*)dataPlayer);


	//add foot sensor fixture
	b2PolygonShape LfootpolygonShape;
	LfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(-(width * UNRATIO +0.1f), height * UNRATIO+0.1f), 0);
	b2FixtureDef LfootFixtureDef;
	LfootFixtureDef.isSensor = true;
	LfootFixtureDef.shape = &LfootpolygonShape;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&LfootFixtureDef);
	FixtureData* dataLFoot = new FixtureData(sf::Color::Green, MonsterLfoot);
	footSensorFixture->SetUserData((void*)dataLFoot);

	b2PolygonShape RfootpolygonShape;
	RfootpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(width * UNRATIO + 0.1f, height * UNRATIO+0.1f), 0);
	b2FixtureDef RfootFixtureDef;
	RfootFixtureDef.isSensor = true;
	RfootFixtureDef.shape = &RfootpolygonShape;
	b2Fixture* RfootSensorFixture = m_body->CreateFixture(&RfootFixtureDef);
	FixtureData* dataRFoot = new FixtureData(sf::Color::Green, MonsterRfoot);
	footSensorFixture->SetUserData((void*)dataRFoot);

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
	playerFixture->SetUserData((void*)playerData);

	
	//add foot sensor fixture
	b2PolygonShape footpolygonShape;
	footpolygonShape.SetAsBox(0.1, 0.1, b2Vec2(0, height*UNRATIO), 0);
	b2FixtureDef footFixtureDef;
	footFixtureDef.isSensor = true;
	footFixtureDef.shape = &footpolygonShape;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&footFixtureDef);
	FootData * dataFoot = new FootData(sf::Color::Green, foot,0);
	footSensorFixture->SetUserData((void*)dataFoot);

	//add hand sensor
	b2PolygonShape handpolygonShape;
	handpolygonShape.SetAsBox(width * UNRATIO+0.1,0.1 , b2Vec2(0, 0), 0);
	b2FixtureDef handfixture;
	handfixture.isSensor = true;
	handfixture.shape = &handpolygonShape;
	b2Fixture* handSensorFixture = m_body->CreateFixture(&handfixture);
	HandData* dataHand = new HandData(sf::Color::Green, hand,0);
	handSensorFixture->SetUserData((void*)dataHand);
	
	return m_body;
}

b2Body* Box2DEngine::addBodyRope(int x, int y, float length, int nb_links) {

	// Link width and height
	float width = length / nb_links;
	float height = 4.0f;

	//shape definition for every link
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(width * UNRATIO, height * UNRATIO);


	// First body : 
	b2BodyDef BodyDefA;
	BodyDefA.type = b2_dynamicBody;


	//create dynamic body
	BodyDefA.position.Set(x * UNRATIO, y * UNRATIO);
	b2Body* bodyA = physicsWorld->CreateBody(&BodyDefA);


	//fixture definition
	b2FixtureDef FixtureDefA;
	FixtureDefA.shape = &polygonShape;
	FixtureDefA.density = 1;
	

	// Fixture userData
	b2Fixture* FixtureA = bodyA->CreateFixture(&FixtureDefA);
	FixtureData* data = new FixtureData(sf::Color::Cyan, rope);
	FixtureA->SetUserData((void*)data);


	b2Body* initBody = bodyA;

	for (int i = 1; i < nb_links; i++) {
		// Body
		b2BodyDef BodyDefB;
		BodyDefB.type = b2_dynamicBody;
		BodyDefB.position.Set(x * UNRATIO + i*width*2*UNRATIO, y * UNRATIO);


		//create dynamic body
		b2Body* bodyB = physicsWorld->CreateBody(&BodyDefB);

		//fixture definition
		b2FixtureDef FixtureDefB;
		FixtureDefB.shape = &polygonShape;
		FixtureDefB.density = 1;

		// Fixture userData
		b2Fixture* FixtureB = bodyB->CreateFixture(&FixtureDefB);
		FixtureData* data = new FixtureData(sf::Color::Cyan, rope);
		FixtureB->SetUserData((void*)data);


		// Link bodyB to bodyA with a revolution joint
		
		b2RevoluteJointDef revoluteJointDef;
		
		revoluteJointDef.bodyA = bodyA;
		revoluteJointDef.bodyB = bodyB;
		revoluteJointDef.collideConnected = false;

		revoluteJointDef.localAnchorA.Set(width*UNRATIO, 0);
		revoluteJointDef.localAnchorB.Set(-width*UNRATIO, 0);
				
		revoluteJointDef.referenceAngle = 0;
		
		physicsWorld.get()->CreateJoint(&revoluteJointDef);
		
		bodyA = bodyB;

	}

	return initBody;
}