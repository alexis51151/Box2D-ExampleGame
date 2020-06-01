#pragma once
#include <box2d/box2d.h>
class Mycontactlisner : public b2ContactListener
{
public:
	Mycontactlisner();
	~Mycontactlisner();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
private:

};

Mycontactlisner::Mycontactlisner()
{
}

Mycontactlisner::~Mycontactlisner()
{
}
