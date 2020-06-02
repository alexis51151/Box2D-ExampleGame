#include "MyContactListener.h"
#include <iostream>
void MyContactListener::BeginContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == foot) { //foot sensor 
        numFootContact++;
    }
    if ((int)fixtureUserData == hand) { //hand sensor 
        numhandContact++;
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == foot) {
        numFootContact++;
    }
    if ((int)fixtureUserData == hand) {
        numhandContact++;
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == foot)
        numFootContact--;
    if ((int)fixtureUserData == hand) {
        numhandContact--;
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == foot)
        numFootContact--;
    if ((int)fixtureUserData == hand) {
        numhandContact--;
    }
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}
