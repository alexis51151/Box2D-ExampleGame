#include "MyContactListener.h"
#include <iostream>
void MyContactListener::BeginContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == 3) { //foot sensor 
        numFootContact++;
    }
    if ((int)fixtureUserData == 4) { //hand sensor 
        numhandContact++;
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == 3) {
        numFootContact++;
    }
    if ((int)fixtureUserData == 4) {
        numhandContact++;
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact--;
    if ((int)fixtureUserData == 4) {
        numhandContact--;
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact--;
    if ((int)fixtureUserData == 4) {
        numhandContact--;
    }
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}