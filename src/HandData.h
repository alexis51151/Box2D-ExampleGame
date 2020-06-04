#pragma once
#include "FixtureData.h"
class HandData:FixtureData
{
public:
	HandData(sf::Color color, int dataType, int numhandContact);
	void IncreaceNumhandContact() { numhandContact++; printf("in hand %d \n", numhandContact); };
	void DecreaceNumhandContact() {	numhandContact--; printf("in hand %d \n", numhandContact);	};

	int GetNumhandContact() const { return numhandContact; }
	void SetNumhandContact(int val) { numhandContact = val; }

protected:

private:
	int numhandContact=0;
};
