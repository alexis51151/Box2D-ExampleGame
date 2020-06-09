#pragma once 
#include "FixtureData.h"
class ViewFieldData : public FixtureData
{
public:
	ViewFieldData::ViewFieldData(sf::Color color, int dataType);
	void increaIncreaceEntitidetected() { entityDetected++; printf("view increased "); };
	void DecreaseEntityDetected() { entityDetected--; };
	int getEntityDetected() const { return entityDetected; }
	void setEntityDetected(int val) { entityDetected = val; }
protected:

private:
	int entityDetected = 0;
};
