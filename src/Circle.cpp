#include "Circle.h"
#include "Shape.h"
#include <iostream> // Pour cout
#include "myMain.h" // Pour toSFMLColor


Circle::Circle(pugi::xml_node node) :
	Shape(node),
	r(node.attribute("r").as_int()),
	color(node.attribute("color").value()) {
}

Circle::Circle(std::string label, int x, int y,  int r, std::string color) :
	Shape(x,y, label), r(r), color(color) {
}

void Circle::arborescence(int absX, int absY, int& i) {
	std::cout << "#" << i << " Circle " << '"' << label << '"' << '/' 
	<< " absolute=(" << (absX + x) << ',' << (absY + y) << ')'
	<< '/' << " relative=(" << x << ',' << y << ')'
	<< '/' << " r=" << r << '/' << " color=" << color << std::endl;
}

void Circle::computeAbsolute(int absX, int absY, TreeCoords& tree, sf::RenderWindow& window) {
	struct Coords c = { absX + x, absY + y };
	// Ajout au vecteur
	tree.push_back(c);
}

void Circle::changeColor(int rank, int& i, std::string option) {
	if (rank == i) {
		color = option;
	}
}

void Circle::translation(int rank, int& i, int delta_x, int delta_y) {
	if (rank == i) {
		Shape::translation(delta_x, delta_y);
	}
}

void Circle::affichage(int absX, int absY, sf::RenderWindow& window) {
	sf::CircleShape circle(r);
	circle.setFillColor(toSFMLColor(color));
	circle.setOrigin(r, r); // dessin à partir du milieu
	circle.setPosition((absX + x) + 960, -(absY +y) + 540); // Le repère SFML est inversé pour l'axe des Y
	window.draw(circle);
}

void Circle::save(std::ofstream& file, int tabs) {
	for (int i = 0; i < tabs; i++) {
		file << "	";
	}
	file << "<Circle" << " label=\"" << label << '"' << " x=\"" << x << '"' << " y=\"" << y << '"' << " r=\"" << r << '"'
		<< " color=\"" << color << '"' << "/>" << std::endl;
}

std::unique_ptr<Shape> Circle::deepCopy() {
	std::unique_ptr<Circle> c(new Circle(label + "copy", x, y, r, color)); 
	return c;
}

void Circle::copy(Shape* father, int rank, int& i) {
	if (rank == i) {
		dynamic_cast<Group*>(father)->add(this->deepCopy());
	}

}

void Circle::add(std::unique_ptr<Shape> c) {

}

