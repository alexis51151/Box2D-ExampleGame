#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>


struct Coords {
	int x;
	int y;
};

using TreeCoords = std::vector<Coords>;

class Shape {
public:
	int x;
	int y;
	std::string label;
	Shape(int, int, std::string);
	Shape();
	Shape(pugi::xml_node);
	virtual void computeAbsolute(int, int, TreeCoords&, sf::RenderWindow&) = 0;
	virtual void affichage(int, int, sf::RenderWindow&) = 0;
	virtual void arborescence(int absX, int absY, int& i) = 0;
	virtual void changeColor(int rank, int& i, std::string option) = 0;
	virtual void translation(int rank, int& i, int delta_x, int delta_y) = 0;
	void translation(int delta_x, int delta_y);
	virtual void save(std::ofstream& file, int tabs) = 0;
	virtual void copy(Shape* father, int rank, int& i) = 0;
	virtual std::unique_ptr<Shape> deepCopy() = 0;
	virtual void add(std::unique_ptr<Shape> c) = 0;


};