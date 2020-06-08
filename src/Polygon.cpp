#include "Polygon.h"

Polygon::Polygon() {

}

void Polygon::draw(b2Body* body, sf::Color color, sf::RenderWindow* window) {
	b2Fixture* fixture = body->GetFixtureList();
	b2PolygonShape* poly;
	b2Vec2 bodyPosition = body->GetPosition();
	switch (fixture->GetType()) {
	case b2Shape::e_polygon: {
		while (fixture->GetNext() != NULL)
		{
			FixtureData* fixtureData = (FixtureData*) fixture->GetUserData();
			if (fixtureData->getDrawable()) {
				poly = (b2PolygonShape*)fixture->GetShape();
				b2Vec2 position = body->GetPosition();
				//sf::VertexArray polygon(sf::Triangles, 3);
				sf::ConvexShape polygon;
				polygon.setPointCount(poly->m_count);
				// Setting position and drawing with SFML
				for (int i = 0; i < poly->m_count; i++) {
					polygon.setPoint(i, sf::Vector2f((bodyPosition.x + poly->m_vertices[i].x) * RATIO, (bodyPosition.y + poly->m_vertices[i].y) * RATIO));
					polygon.setOutlineColor(sf::Color::Red);
					polygon.setFillColor(sf::Color::Blue);
					//polygon[i].position = sf::Vector2f((bodyPosition.x + poly->m_vertices[i].x )* RATIO, (bodyPosition.y + poly->m_vertices[i].y) * RATIO);
					//polygon[i].color = color;
				}
				
				window->draw(polygon);
			}
			fixture = fixture->GetNext();
		}
		break;
	}
	default:
		printf("No drawing available for this fixture type\n");
	}
}