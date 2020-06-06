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

PlayerData* getPlayerData(b2Body* player1) {
	b2Fixture* playerfixtures = player1->GetFixtureList();
	while (playerfixtures != nullptr) {
		FixtureData* userdata = ((FixtureData*)playerfixtures->GetUserData());
		if (userdata->getDataType() == player)
			return (PlayerData*)userdata;
		playerfixtures = playerfixtures->GetNext();
	}
}

std::pair<int, int> getBodyDimensions(b2Body* body) { // only for polygons right now :Not working:
	b2Fixture* fixture = body->GetFixtureList();
	int width, height;
	switch (fixture->GetType()) {
	case b2Shape::e_polygon: {
		while (fixture->GetNext() != NULL)
		{
			fixture = fixture->GetNext();
		}
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();

		width = sqrt(pow((poly->m_vertices[1].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[1].y - poly->m_vertices[0].y), 2));
		height = sqrt(pow((poly->m_vertices[3].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[3].y - poly->m_vertices[0].y), 2));
		//printf("width: %f \n", width);
		//printf("heigth: %f \n", height);
		break;
	}
	default:
		printf("No drawing available for this fixture type\n");
		return std::make_pair(NULL,NULL);
	}
	return std::make_pair(width, height);
}