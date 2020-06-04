#include <FixtureData.h>
#include <Global.h>



FixtureData::FixtureData(sf::Color color=sf::Color::Black, int dataType=default) : color(color), dataType(dataType) {

}

FixtureData::FixtureData()
{

}

FixtureData::~FixtureData() {

}

sf::Color FixtureData::getColor() {
	return color;
}

void FixtureData::setColor(sf::Color color) {
	FixtureData::color = color;
}

int FixtureData::getDataType() {
	return dataType;
}

void FixtureData::setDataType(int dataType) {
	FixtureData::dataType = dataType;
}
