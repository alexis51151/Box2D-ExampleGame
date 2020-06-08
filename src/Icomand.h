#pragma once
class Icommand
{
public:
	virtual void execute(Player* player) = 0;
	virtual ~Icommand() {};
private:

};
