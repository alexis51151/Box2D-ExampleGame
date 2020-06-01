#include "Mycontactlisner.h"
#include"Global.h"

void Mycontactlisner::BeginContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact++;
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact++;
}

void Mycontactlisner::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact--;
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == 3)
        numFootContact--;
}
