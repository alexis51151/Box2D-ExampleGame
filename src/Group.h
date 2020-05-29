#pragma once

#include <string>
#include <pugixml.hpp>
#include <iostream>
#include "Circle.h"
#include "Shape.h"
#include <SFML/Graphics.hpp>

class Group : public Shape{
public:
	Group(pugi::xml_node node);
	Group(std::string label, int x, int y);
	void add(std::unique_ptr<Shape> c);
	std::vector<std::unique_ptr<Shape>> elements;
	void computeAbsolute(int, int, TreeCoords&,sf::RenderWindow&);
	void affichage(int , int, sf::RenderWindow&);
	void arborescence(int absX, int absY, int& i);
	void changeColor(int rank, int& i, std::string option);
	void translation(int rank, int& i, int delta_x, int delta_y);
	void save(std::ofstream& file, int tabs);
	void copy(Shape* father, int rank, int& i);
	std::unique_ptr<Shape> deepCopy();
};
