#include "myMain.h"
#include "Global.h"
#include "Draw.h"

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
	Box2dEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();

	// Define the dynamic body. We set its position and call the body factory.
	b2Body* player =gameController.addDynamicBox( 10 * RATIO , 10 * RATIO , 1.0f * RATIO, 1.0f * RATIO,Material::DEFAULT);
	
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	sf::CircleShape c(1.0f*RATIO);
	c.setFillColor(sf::Color::Green);
	sf::RectangleShape r(sf::Vector2f(8.0f*2* RATIO, 1.0f *2* RATIO));
	r.setFillColor(sf::Color::Red);


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
				gameController.addDynamicBox(MouseX, MouseY, 1.0f * RATIO, 1.0f * RATIO,Material::WOOD);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				float MouseX = sf::Mouse::getPosition(*window).x;
				float MouseY = sf::Mouse::getPosition(*window).y;
				gameController.addStaticBox(MouseX, MouseY, 8.0f * RATIO, 2.0f * RATIO);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(-10, 0), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(10, 0), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(0, 10), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player->ApplyLinearImpulseToCenter(b2Vec2(0, -10), true);
			}
		}
		
		window->clear(sf::Color::White);
		world->Step(timeStep, velocityIterations, positionIterations);
		int BodyCount = 0;
		for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				DrawShape(BodyIterator, &c, window);
			}
			if (BodyIterator->GetType() == b2_staticBody)
			{
				DrawShape(BodyIterator, &r, window);
			}
		}
		window->display();
	}

	return 0;
}

