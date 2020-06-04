#include "MyContactListener.h"
#include <iostream>
void MyContactListener::BeginContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    FixtureData* fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot) { //foot sensor 
            ((FootData*)fixtureData)->IncreaceNumFootContact();
        }
        if ((int)fixtureData->getDataType() == hand) { //hand sensor 
            ((HandData*)fixtureData)->IncreaceNumhandContact();
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot) {
            ((FootData*)fixtureData)->IncreaceNumFootContact();
        }
        if ((int)fixtureData->getDataType() == hand) {
            ((HandData*)fixtureData)->IncreaceNumhandContact();
        }
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    FixtureData* fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot)
            ((FootData*)fixtureData)->DecreaceNumFootContact();
        if ((int)fixtureData->getDataType() == hand) {
            ((HandData*)fixtureData)->DecreaceNumhandContact();
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    fixtureData = (FixtureData*)fixtureUserData;
    if (fixtureData != NULL) {
        if ((int)fixtureData->getDataType() == foot)
            ((FootData*)fixtureData)->DecreaceNumFootContact();
        if ((int)fixtureData->getDataType() == hand) {
            ((HandData*)fixtureData)->DecreaceNumhandContact();
        }
    }
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}
