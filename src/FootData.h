#pragma once
#include "FixtureData.h"
class FootData:FixtureData
{
public:
	FootData(sf::Color color, int dataType, int numFootContact = 0);
	int	GetNumFootContact() const { return numFootContact; }
	void SetNumFootContact(int val) { numFootContact = val; }
	void IncreaceNumFootContact() { numFootContact++; }
	void DecreaceNumFootContact() { numFootContact--; }
protected:

private:
	int numFootContact = 0;
};
