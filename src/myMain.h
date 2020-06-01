#pragma once

#include "Group.h"
#include "Circle.h"
#include "Shape.h"
#include <pugixml.hpp>
#include <iostream> // Pour cout
#include <fstream> // Pour lire visage.xml
#include <string>  // pour copier visage.xml
#include <sstream> //std::stringstream
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Box2DEngine.h"
#include <cmath>



int myMain();
Group arborescence(std::string s);
sf::Color toSFMLColor(std::string color);