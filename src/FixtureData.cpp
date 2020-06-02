#include <FixtureData.h>
#include <Global.h>


FixtureData::FixtureData(sf::Color color) : color(color) {

}

FixtureData::FixtureData(sf::Color color, int dataType) : color(color), dataType(dataType) {

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
