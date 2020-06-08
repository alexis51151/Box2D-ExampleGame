#pragma once 
#include "FixtureData.h"
class ViewFieldData : public FixtureData
{
public:
	ViewFieldData::ViewFieldData(sf::Color color, int dataType);
	void increaIncreaceEntitidetected() { entitidetected++; printf("view incresed "); };
	void DecreaseEntityDetected() { entitidetected--; };
	int getEntitidetected() const { return entitidetected; }
	void setEntitidetected(int val) { entitidetected = val; }
protected:

private:
	int entitidetected = 0;
};
