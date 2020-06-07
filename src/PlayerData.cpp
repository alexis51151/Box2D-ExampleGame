#include "PlayerData.h"


PlayerData::PlayerData()
{
}

PlayerData::PlayerData(sf::Color color, int dataType, int m_jumpTimeout):FixtureData(color, dataType),m_jumpTimeout(m_jumpTimeout)
{

}

PlayerData::~PlayerData()
{
}
