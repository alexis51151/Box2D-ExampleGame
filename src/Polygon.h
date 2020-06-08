#pragma once

class Polygon : public Shape {
public:
	Polygon();
	void draw(b2Body*, sf::Color, sf::RenderWindow*);
};