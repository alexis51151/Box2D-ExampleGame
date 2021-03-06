#pragma once

#include <pugixml.hpp>
#include <iostream> // Pour cout
#include <fstream> // Pour lire visage.xml
#include <string>  // pour copier visage.xml
#include <sstream> //std::stringstream
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Box2DEngine.h"
#include <cmath>
#include "Global.h"
#include "Draw.h"
#include "Events.h"
#include "MyContactListener.h"
#include "Player.h"
#include "Monster.h"
#include "Platform.h"
#include <memory>
#include "Rope.h"
#include "XMLParser.h"
#include <windows.h>


int myMain();
