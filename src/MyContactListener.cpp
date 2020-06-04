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
            printf("hand touche \n");
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
            printf("hand touche \n");
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
            printf("hand touche plus \n");
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
            printf("hand touche plus \n");
        }
    }
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}
