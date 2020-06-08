#include "MyContactListener.h"
#include <iostream>


void viewdetextion(b2Fixture * A, b2Fixture* B) {
	FixtureData* fixtureDataA = static_cast<FixtureData*> (A->GetUserData());
	FixtureData* fixtureDataB = static_cast<FixtureData*> (B->GetUserData());
	if (  fixtureDataA->getDataType() == viewField ){
		printf("champ de vision activer\n");
		b2RayCastInput input;
		input.p1 = A->GetBody()->GetWorldCenter();
		input.p1 = B->GetBody()->GetWorldCenter();
		input.maxFraction = 1;
		b2RayCastOutput* output=new b2RayCastOutput();;
		if (A->RayCast(output, input, 0)) {
			printf("il ya un element entre les deux \n");
		}
		else
		{
			printf("il n'y a rien entre les deux \n");
		}

	}
	if (fixtureDataB->getDataType() == viewField) {
		printf("champ de vision activer\n");
		b2RayCastInput input;
		input.p1 = B->GetBody()->GetWorldCenter();
		input.p1 = A->GetBody()->GetWorldCenter();
		input.maxFraction = 1;
		b2RayCastOutput* output = new b2RayCastOutput();
		if (B->RayCast(output, input, 0)) {
			printf("il ya un element entre les deux \n");
		}
		else
		{
			printf("il n'y a rien entre les deux \n");
		}

	}


}
void end_contact_action(FixtureData* fixtureData) {
	switch (fixtureData->getDataType())
	{
	case foot:
		((FootData*)fixtureData)->DecreaceNumFootContact(); //me laisse pas static cast 
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
	
	if (contact->GetFixtureA() != NULL && contact->GetFixtureB() != NULL) {
		viewdetextion(contact->GetFixtureA(), contact->GetFixtureB());
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
