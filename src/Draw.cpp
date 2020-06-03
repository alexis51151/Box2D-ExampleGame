#include <Draw.h>



// Function for drawing a shape using SFML 
// Only implements box2D fixtures that are rectangles (ie fixtures initialized using b2Fixture::setAsBox)
void DrawShape(b2Body* body, sf::Color color, sf::RenderWindow* window) {
	float width = 0;
	float height = 0;
	b2Fixture* fixture = body->GetFixtureList();
	switch (fixture->GetType()) {
	case b2Shape::e_polygon: {
		while (fixture->GetNext()!= NULL)
		{
			fixture = fixture->GetNext();
		}
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
		
		width = sqrt(pow((poly->m_vertices[1].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[1].y - poly->m_vertices[0].y), 2));
		height = sqrt(pow((poly->m_vertices[3].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[3].y - poly->m_vertices[0].y), 2));
		printf("width: %f \n", width);
		printf("heith: %f \n", height);
		break;
	}
	default:
		perror("No drawing available for this fixture type\n");
		return;
	}
	b2Vec2 position = body->GetPosition();
	void* fixtureUserData = fixture->GetUserData();
	FixtureData* fixtureData = (FixtureData*)fixtureUserData;

	if (fixtureData == NULL) {
		perror("No fixture data linked to that body\n");
		return;
	}
	int dataType = (int)fixtureData->getDataType();
	sf::Shape* shape;
	switch (dataType) {
	case (player || default):
	{
		sf::CircleShape c(width * RATIO);
		c.setFillColor(color);
		shape = &c;
	}
	case platform:
	{
		sf::RectangleShape r(sf::Vector2f(8.0f * 2 * RATIO, 1.0f * 2 * RATIO)); // *2 because box2D takes mid-height and mid-width 
		r.setFillColor(sf::Color::Red);
		shape = &r;
	}
	default:
	{
		perror("Not drawable dataType\n");
		return;
	}
	}

	// Setting position and drawing with SFML
	shape->setPosition((position.x - width / 2) * RATIO, (position.y - height / 2) * RATIO);
	window->draw(*shape);
}