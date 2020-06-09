#pragma once

class PlayerRighttcomand : public Icommand
{
public:
	virtual void execute(Player* player) override {
		player->actionRight();
	}
private:

};
