#pragma once
#include "pugixml.hpp"
#include <iostream> /
#include <fstream> 
#include <string>  
#include <sstream> //std::stringstream
#include <map>
#include <string>

class XMLParser {
public:
	XMLParser(std::string configPath);
	int readConfig();
	std::map<std::string, int> getWorldParameters() const { return worldParameters; }
	std::string getConfig() const { return config; }
	std::map<std::string, int> getKeyboardCommandsPlayer1() const { return keyboardCommandsPlayer1; }
	std::map<std::string, int> getKeyboardCommandsPlayer2() const { return keyboardCommandsPlayer2; }

private:
	std::map<std::string, int>	keyboardCommandsPlayer1;
	std::map<std::string, int>	keyboardCommandsPlayer2;
	std::map<std::string, int>	worldParameters;
	std::string config;
};