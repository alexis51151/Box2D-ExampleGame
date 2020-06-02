#include "MyContactListener.h"
#include <iostream>
void MyContactListener::BeginContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    FixtureData* fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot) { //foot sensor 
            numFootContact++;
        }
        if ((int)fixtureData->getDataType() == hand) { //hand sensor 
            numhandContact++;
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot) {
            numFootContact++;
        }
        if ((int)fixtureData->getDataType() == hand) {
            numhandContact++;
        }
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    FixtureData* fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot)
            numFootContact--;
        if ((int)fixtureData->getDataType() == hand) {
            numhandContact--;
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot)
            numFootContact--;
        if ((int)fixtureData->getDataType() == hand) {
            numhandContact--;
        }
    }
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}
