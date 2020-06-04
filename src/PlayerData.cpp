#include "PlayerData.h"

PlayerData::PlayerData()
{
}

PlayerData::PlayerData(sf::Color color, int dataType, int canJump=0):FixtureData(color,dataType),canJump(canJump)
{

}

PlayerData::~PlayerData()
{
}
