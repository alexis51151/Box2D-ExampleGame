#pragma once 
#include "FixtureData.h"
class PlayerData:FixtureData
{
public:
	PlayerData();
	PlayerData(sf::Color color, int dataType,int m_jumpTimeout = 0);
	~PlayerData();
	
	int GetJumpTimeout() const { return m_jumpTimeout; }
	void SetJumpTimeout(int val) { m_jumpTimeout = val; }
	void decreaseJumpTimeout() { m_jumpTimeout--; }

private:
	int m_jumpTimeout=0;
};

