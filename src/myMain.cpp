#include "myMain.h"

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
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Outil de visualisation"); // Variable globale pour la fenêtre 
	window.clear(sf::Color::White);

	// Lecture du fichier XML
	std::ifstream visageXML("C:\\Users\\alexi\\source\\repos\\Jeu_jin\\resources\\visage.xml");
	if (!visageXML) {
		std::cout << "Chemin d'acces errone" << std::endl;
	}
	std::stringstream visageStream;
	visageStream << visageXML.rdbuf();
	std::string visage = visageStream.str();
	Group init = arborescence(visage);
	visageXML.close();

	// Dessin des éléments
	//init.affichage(0,0,window);
	//window.display();

	//Test pour relier Box2DEngine à SFML 
	
	//Partie initialisation Box2D
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2Body* groundBody = create_ground_body(world);

	// Define the dynamic body. We set its position and call the body factory.
	b2Body* player = create_body(world);
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	
	sf::CircleShape c(10);
	sf::RectangleShape r(sf::Vector2f(50,10));
	r.setFillColor(sf::Color::Red);
	c.setFillColor(sf::Color::Green);
	b2Vec2 position;
	// Boucle d'événements SFML
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int MouseX = sf::Mouse::getPosition(window).x;
				int MouseY = sf::Mouse::getPosition(window).y;
				create_body_with_pose(world, MouseX / 10, MouseY / 10);
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
		
		window.clear(sf::Color::White);
		world.Step(timeStep, velocityIterations, positionIterations);
		int BodyCount = 0;
		for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				position = BodyIterator->GetPosition();
				c.setPosition(10 * position.x, 10 * position.y);
				window.draw(c);
				printf("%4.2f %4.2f\n", position.x, position.y);
				BodyCount++;
			}
			if (BodyIterator->GetType() == b2_staticBody)
			{
				window.draw(r);
			}
		}
		window.display();

	}

	return 0;
}

