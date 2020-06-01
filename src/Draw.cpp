#include <Draw.h>
#include <SFML/Graphics.hpp>



// Function for drawing a shape using SFML 
// Only implements box2D fixtures that are rectangles (ie fixtures initialized using b2Fixture::setAsBox)
void DrawShape(b2Body* body, sf::Shape* shape, sf::RenderWindow* window) {
	float width = 0;
	float height = 0;
	b2Fixture* fixture = body->GetFixtureList();
	switch (fixture->GetType()) {
	case b2Shape::e_polygon: {
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
		width = sqrt(pow((poly->m_vertices[1].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[1].y - poly->m_vertices[0].y), 2));
		height = sqrt(pow((poly->m_vertices[3].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[3].y - poly->m_vertices[0].y), 2));
		break;
	}
	default:
		perror("No drawing available for this fixture type\n");
		return;
	}
	b2Vec2 position = body->GetPosition();
	(*shape).setPosition((position.x - width / 2) * RATIO, (position.y - height / 2) * RATIO);
	window->draw(*shape);
}