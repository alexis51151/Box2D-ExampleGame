#include "MyContactListener.h"
#include <iostream>

void MyContactListener::BeginContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    std::cout << "Valeur de UserData:" << (int)fixtureUserData << std::endl;

    if ((int)fixtureUserData == 3)
        numFootContact++;
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact++;
}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact--;
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact--;
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}
