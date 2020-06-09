#pragma once
#include "Shape.h"
#include "box2d/box2d.h"
#include "Global.h"
#include "FixtureData.h"
#include "Utile.h"


class Rectangle : public Shape {
public:
	Rectangle();
	void draw(b2Body*, sf::Color, sf::RenderWindow*);

};