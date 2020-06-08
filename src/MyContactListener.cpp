#include "MyContactListener.h"
#include <iostream>


void end_contact_action(FixtureData* fixtureData) {
	switch (fixtureData->getDataType())
	{
	case foot:
		((FootData*)fixtureData)->DecreaceNumFootContact(); //me laisse pas static cast 
		break;
	case viewField:
		printf("un champ de vue a été désactivé \n");
		((ViewFieldData*)fixtureData)->DecreaseEntityDetected(); //me laisse pas static cast 
		break;
	case MonsterLfoot:
		((FootData*)fixtureData)->DecreaceNumFootContact();
		break;
	case MonsterRfoot:
		((FootData*)fixtureData)->DecreaceNumFootContact();
		break;
	case hand:
		((HandData*)fixtureData)->DecreaceNumhandContact();
		break;
	default:
		break;
	}
}

void BeginContact_action(FixtureData* fixtureData) {
	switch (fixtureData->getDataType())
	{
	case foot:
		((FootData*)fixtureData)->IncreaceNumFootContact();
		break;
	case viewField:
		printf("un champ de vue a été activé \n");
		((ViewFieldData*)fixtureData)->increaIncreaceEntitidetected(); //me laisse pas static cast 
		break;
	case MonsterLfoot:
		((FootData*)fixtureData)->IncreaceNumFootContact();
		break;
	case MonsterRfoot:
		((FootData*)fixtureData)->IncreaceNumFootContact();
		break;
	case hand:
		((HandData*)fixtureData)->IncreaceNumhandContact();
		break;
	default:
		break;
	}
}

void MyContactListener::BeginContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    FixtureData* fixtureData = static_cast<FixtureData*>( fixtureUserData );
    if (fixtureData != NULL) {
		BeginContact_action(fixtureData);
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    fixtureData = static_cast<FixtureData*>( fixtureUserData );
    if (fixtureData != NULL) {
		BeginContact_action(fixtureData);
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	FixtureData* fixtureData = static_cast<FixtureData*>(fixtureUserData);
    if (fixtureData != NULL) {
        end_contact_action(fixtureData);
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
	fixtureData = static_cast<FixtureData*>(fixtureUserData);
    if (fixtureData != NULL) {
        end_contact_action(fixtureData);
    }
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}
