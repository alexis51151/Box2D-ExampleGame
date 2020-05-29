#pragma once

#include <string>
#include "Group.h"
#include <Shape.h>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>



class Circle : public Shape{
public:
	Circle(pugi::xml_node node);
	Circle(std::string label, int x, int y,  int r, std::string color);
	void computeAbsolute(int, int, TreeCoords&, sf::RenderWindow&);
	void affichage(int, int, sf::RenderWindow&);
	void arborescence(int absX, int absY, int& i);
	void changeColor(int rank, int& i, std::string option);
	int r;
	std::string color;
	void translation(int rank, int& i, int delta_x, int delta_y);
	void save(std::ofstream& file, int tabs);
	void copy(Shape* father, int rank, int& i);
	std::unique_ptr<Shape> deepCopy();
	void add(std::unique_ptr<Shape> c);

};


