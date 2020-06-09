#pragma once
<<<<<<< HEAD
#include "Icomand.h"
=======

>>>>>>> fcf14ea275641dd9d13ad2600cb359de9f125d58
class PlayerRighttcomand : public Icommand
{
public:
	virtual void execute(Player* player) override {
		player->actionRight();
	}
private:

};
