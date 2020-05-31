#include "Box2DEngine.h"
#include "Global.h"

b2Body* create_platform(b2World& world, float posx , float posy) {
	// Define the ground body.
	b2BodyDef platformeBodyDef;
	platformeBodyDef.type = b2_staticBody;
	platformeBodyDef.position.Set(posx*UNRATIO, posy*UNRATIO);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&platformeBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(8.0f, 1.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
	return groundBody;
}


b2Body* create_body(b2World& world,float x , float y ) {
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	printf("taille : %f , %f ; %f ,%f ", x, y, x * UNRATIO, y * UNRATIO);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
	return body;
}