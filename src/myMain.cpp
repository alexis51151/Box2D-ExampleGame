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
	init.affichage(0,0,window);
	window.display();

	// Boucle d'événements SFML
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}