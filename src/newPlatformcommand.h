#pragma once
#include <iostream>
#include "Icomand.h"
class Newplatformcommand: public Icommand
{
public:
	virtual void execute(Player * player) override {
		std::cout << "newplatform\n\n\n\n\n\n"<<std::endl;
	}
private:

};

