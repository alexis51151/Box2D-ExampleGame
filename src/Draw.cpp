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
		//printf("width: %f \n", width);
		//printf("heigth: %f \n", height);
		break;
	}
	default:
		printf("No drawing available for this fixture type\n");
		return;
	}
	b2Vec2 position = body->GetPosition();
	void* fixtureUserData = fixture->GetUserData();
	FixtureData* fixtureData = (FixtureData*)fixtureUserData;

	if (fixtureData == NULL) {
		//printf("No fixture data linked to that body\n");
		return;
	}
	int dataType = (int)fixtureData->getDataType();
	std::unique_ptr<sf::Shape> shape;
	switch (dataType) {
	case player:
	{
		std::unique_ptr<sf::CircleShape> c(new sf::CircleShape(width/2 * RATIO));
		c.get()->setFillColor(color);
		shape = std::move(c);
		break;
	}
	case default:
	{
		std::unique_ptr<sf::CircleShape> c(new sf::CircleShape(width/2 * RATIO));
		c.get()->setFillColor(color);
		shape = std::move(c);
		break;
	}
	case platform:
	{
		std::unique_ptr<sf::RectangleShape> r(new sf::RectangleShape(sf::Vector2f(width * RATIO, height * RATIO)));
		r.get()->setFillColor(sf::Color::Red);
		shape = std::move(r);
		break;
	}
	case rope:
	{
		std::unique_ptr<sf::RectangleShape> r(new sf::RectangleShape(sf::Vector2f(width * RATIO, height * RATIO)));
		r.get()->setFillColor(sf::Color::Red);
		shape = std::move(r);
		break;
	}
	default:
	{
		printf("Not drawable dataType : %d\n", dataType);
		return;
	}
	}

	// Setting position and drawing with SFML
	shape->setPosition((position.x - width / 2) * RATIO, (position.y - height / 2) * RATIO);
	window->draw(*shape);
}