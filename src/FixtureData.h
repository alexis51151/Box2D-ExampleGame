#pragma once

#include <SFML/Graphics.hpp>
#include <Global.h>

class FixtureData
{
public:
	FixtureData(sf::Color color);
	FixtureData(sf::Color color, int dataType);
	~FixtureData();
	sf::Color getColor();
	void setColor(sf::Color color);
	int getDataType();
	void setDataType(int dataType);
private:
	int dataType = end;
	sf::Color color;
};
