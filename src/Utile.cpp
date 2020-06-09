#include "Utile.h"


std::pair<float, float> getBodyDimensions(b2Body* body) { // only for squares right now 
	b2Fixture* fixture = body->GetFixtureList();
	float width, height;
	switch (fixture->GetType()) {
	case b2Shape::e_polygon: {
		while (fixture->IsSensor() && fixture->GetNext() != NULL)
		{
			fixture = fixture->GetNext();
		}
		if (fixture->IsSensor()) {
			return std::make_pair(NULL, NULL); //no drawable feature in this body 
		}
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();

		width = sqrt(pow((poly->m_vertices[1].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[1].y - poly->m_vertices[0].y), 2));
		height = sqrt(pow((poly->m_vertices[3].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[3].y - poly->m_vertices[0].y), 2));

		break;
	}
	default:
		printf("No drawing available for this fixture type\n");
		return std::make_pair(NULL,NULL);
	}
	return std::make_pair(width, height);
}