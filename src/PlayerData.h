#include "FixtureData.h"
class PlayerData:FixtureData
{
public:
	PlayerData();
	PlayerData(sf::Color color, int dataType, int canJump);
	~PlayerData();

private:
	int canJump = 0;
};

