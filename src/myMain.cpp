#include "myMain.h"
#include "Global.h"

sf::Color toSFMLColor(std::string color) {
	if (color == "Black") {
		return sf::Color::Black;
	}
	if (color == "White") {
		return sf::Color::White;
	}
	if (color == "Red") {
		return sf::Color::Red;
	}
	if (color == "Green") {
		return sf::Color::Green;
	}
	if (color == "Blue") {
		return sf::Color::Blue;
	}
	if (color == "Yellow") {
		return sf::Color::Yellow;
	}
	if (color == "Magenta") {
		return sf::Color::Magenta;
	}
	if (color == "Cyan") {
		return sf::Color::Magenta;
	}
	if (color == "Transparent") {
		return sf::Color::Magenta;
	}
	else {
		return sf::Color::White; // Si on ne reconnait pas la couleur
	}
}

Group arborescence(std::string s) {
	// variables pugixml
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	pugi::xml_node drawing = doc.child("Drawing");
	Group draw("root (member of Drawing)", 0, 0);
	for (pugi::xml_node child : drawing.children()) { // parcours des fils du dessin
		if (!strcmp(child.name(), "Circle")) {
			draw.add(std::unique_ptr<Circle>(new Circle(child)));
		}
		else if (!strcmp(child.name(), "Group")) {
			draw.add(std::unique_ptr<Group>(new Group(child)));
		}
	}
	return draw;
}

int myMain() {
	// Initialisation SFML
	Box2dEngine gamecontroleur(WIDTH, HEIGHT);
	b2World* world = gamecontroleur.getPhysicsWorld();
	sf::RenderWindow* window = gamecontroleur.getApp();

	// Define the dynamic body. We set its position and call the body factory.
	b2Body* player =gamecontroleur.create_body(10*RATIO,10*RATIO);
	
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	sf::CircleShape c(1.0f*RATIO);
	c.setFillColor(sf::Color::Green);
	sf::RectangleShape r(sf::Vector2f(8.0f*2* RATIO, 1.0f *2* RATIO));
	r.setFillColor(sf::Color::Red);
	b2Vec2 position;


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				float MouseX = sf::Mouse::getPosition(*window).x;
				float MouseY = sf::Mouse::getPosition(*window).y;
				gamecontroleur.create_body(MouseX, MouseY);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				float MouseX = sf::Mouse::getPosition(*window).x;
				float MouseY = sf::Mouse::getPosition(*window).y;
				gamecontroleur.create_platform(MouseX, MouseY);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(-100, 0), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(100, 0), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(0, 100), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(0, -100), true);
			}
		}
		
		window->clear(sf::Color::White);
		world->Step(timeStep, velocityIterations, positionIterations);
		int BodyCount = 0;
		for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				position = BodyIterator->GetPosition();
				c.setPosition((position.x-1) * RATIO, (position.y-1 ) * RATIO); //devrais etre -1 mais pas centrer 

				window->draw(c);
				BodyCount++;
			}
			if (BodyIterator->GetType() == b2_staticBody)
			{
				float width = 0;
				float height = 0;
				b2Fixture* fixture = BodyIterator->GetFixtureList();
				if (fixture->GetType() == b2Shape::e_polygon) {
					b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
					std::cout << "Structure du tableau\n";
					width = sqrt(pow((poly->m_vertices[1].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[1].y - poly->m_vertices[0].y), 2));
					height = sqrt(pow((poly->m_vertices[3].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[3].y - poly->m_vertices[0].y), 2));
				}
				position = BodyIterator->GetPosition();
				r.setPosition((position.x-width/2) * RATIO, (position.y-height/2)* RATIO);
				window->draw(r);
			}
		}
		window->display();
	}

	return 0;
}

