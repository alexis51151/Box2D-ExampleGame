#pragma once

#include <SFML/Graphics.hpp>
#include <Global.h>

class FixtureData
{
public:
	FixtureData(sf::Color color, int dataType);
	FixtureData();
	~FixtureData();
	sf::Color getColor();
	void setColor(sf::Color color);
	int getDataType();
	void setDataType(int dataType);
private:
	int dataType = default;
	sf::Color color;
};
