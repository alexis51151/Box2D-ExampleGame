#pragma once
#include "FixtureData.h"
class HandData:FixtureData
{
public:
	HandData(sf::Color color, int dataType, int numhandContact);
	void IncreaceNumhandContact() { numhandContact++; };
	void DecreaceNumhandContact() { numhandContact--; };

	int GetNumhandContact() const { return numhandContact; }
	void SetNumhandContact(int val) { numhandContact = val; }

protected:

private:
	int numhandContact;
};
