#include "Utile.h"
void getvalue(b2Body* player1, int* footcount, int* handcount, int* jumptimout) {
	b2Fixture* playerfixtures = player1->GetFixtureList();
	while (playerfixtures != nullptr) {
		FixtureData* userdata = ((FixtureData*)playerfixtures->GetUserData());
		if (userdata == nullptr)
			return;
		int datatype = userdata->getDataType();
		switch (datatype)
		{
		case foot:
			*footcount = ((FootData*)userdata)->GetNumFootContact();
			break;
		case hand:
			*handcount = ((HandData*)userdata)->GetNumhandContact();
			break;
		case player:
			*jumptimout = ((PlayerData*)userdata)->GetJumpTimeout();
			break;
		default:
			printf("attention type de features non prisent en compte ");
			break;
		}
		playerfixtures = playerfixtures->GetNext();
	}
}
