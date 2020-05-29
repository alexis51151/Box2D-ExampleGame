#include "Group.h"
#include <fstream>

Group::Group(pugi::xml_node node) :
	Shape(node) {
	std::cout << node.name() << std::endl;
	for (pugi::xml_node child : node.children()) { // parcours des fils du groupe
		if (!strcmp(child.name(), "Group")) {
			elements.push_back(std::unique_ptr<Group>(new Group(child))); 
		}
		if (!strcmp(child.name(), "Circle")) {
			elements.push_back(std::unique_ptr<Circle>(new Circle(child))); 
		}
	}
}

Group::Group(std::string label, int x, int y) :
	Shape(x, y, label){
}

void Group::add(std::unique_ptr<Shape> c) {
	//elements.push_back(c);
	elements.push_back(std::move(c));
}

void Group::arborescence(int absX, int absY, int& i) {
	std::cout << "#" << i << " Group " << '"' << label << '"' << '/'
		<< " absolute=(" << (absX + x) << ',' << (absY + y) << ')'
		<< '/' << " relative=(" << x << ',' << y << ')' << std::endl;

	for (auto& e : elements) {
		i++;
		e->arborescence(absX + x, absY + y, i);
	}
}


void Group::computeAbsolute(int absX, int absY, TreeCoords &tree, sf::RenderWindow& window)
{
	// Passage en struct
	struct Coords parent_coords = { absX + x, absY + y };
	tree.push_back(parent_coords);
	for (auto& e : elements) {
		e->computeAbsolute(absX + x, absY + y, tree, window);
	}
}

void Group::affichage(int absX, int absY, sf::RenderWindow& window) {
	// Passage en struct
	for (auto& e : elements) {
		e->affichage(absX + x, absY + y, window);
	}
}


void Group::changeColor(int rank, int& i, std::string option) {
	if (i < rank) {
		for (auto& e : elements) {
			i++;
			e->changeColor(rank, i, option);
		}
	}
}

void Group::translation(int rank, int& i, int delta_x, int delta_y) {
	if (rank == i) {
		Shape::translation(delta_x, delta_y);
	}
	else if (i < rank) {
		for (auto& e : elements) {
			i++;
			e->translation(rank, i, delta_x, delta_y);
		}
	}
}


void Group::save(std::ofstream& file, int tabs) {
	if (label == "root (member of Drawing)") { // Cas particulier : racine 
		file << "<?xml version=\"1.0\"?>" << std::endl;
		file << "<Drawing>" << std::endl;
		for (auto& e : elements) {
			e->save(file, tabs+1);
		}
		file << "</Drawing>" << std::endl;
	}
	else {
		// Indentation
		for (int i = 0; i < tabs; i++) { 
			file << "	";
		}
		// Affichage balise ouvrante
		file << "<Group" << " label=" << '"' << label << '"' << " x=" << '"' << x << '"' << " y=" << '"' << y << '"' << ">" << std::endl;
		
		// Parcours des enfants
		for (auto& e : elements) {
			e->save(file, tabs+1);
		}

		// Affichage balise fermante
		for (int i = 0; i < tabs; i++) {
			file << "	";
		}
		file << "</Group>" << std::endl;
	}
}

std::unique_ptr<Shape> Group::deepCopy() {
	std::unique_ptr<Group> g(new Group(label + "copy", x , y));
	for (auto& e : elements) {
		g->add(e->deepCopy());
	}
	return g;
}


void Group::copy(Shape* father, int rank, int& i) {
	if (rank == i) {
		father->add(this->deepCopy());
	}
	else if (i < rank) {
		for (auto& e : elements) {
			if (i < rank) { // On va ajouter un élément à elements en cours de route, ça plante si on continue le parcours après le rajout
				i++;
				e->copy(this, rank, i);
			}
		}
	}
}


