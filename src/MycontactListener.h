#pragma once
#include <box2d/box2d.h>
#include "Global.h"

extern int numFootContact;
extern int numhandContact;

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
private:

};

