#pragma once
#include "Icomand.h"
class PlayerRighttcomand : public Icommand
{
public:
	virtual void execute(Player* player) override {
		player->actionRight();
	}
private:

};
