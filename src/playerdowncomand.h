#pragma once
#include "Icomand.h"
class PlayerDowncomand : public Icommand
{
public:
	virtual void execute(Player* player) override {
		player->actionDown();
	}
private:

};

