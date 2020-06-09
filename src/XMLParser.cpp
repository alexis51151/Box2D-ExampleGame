#include "XMLParser.h"
namespace fs = std::experimental::filesystem;


XMLParser::XMLParser(std::string configPath) {
	std::ifstream XMLConfig(configPath);
	if (!XMLConfig) {
		std::cout << "Wrong path" << std::endl;
	}
	else {
		std::stringstream XMLConfigStream;
		XMLConfigStream << XMLConfig.rdbuf();
		XMLParser::config = XMLConfigStream.str();
	}
	XMLConfig.close();
}


int XMLParser::readConfig() {
	if (config == "") {
		std::cout << "Config not loaded" << std::endl;
		return -1;
	}
	// pugixml loading
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(getConfig().c_str());

	// World parameters
	pugi::xml_node world = doc.child("World");
	for (pugi::xml_attribute attr : world.attributes()) {
		worldParameters[attr.name()] = attr.as_int();
	}
	// Players keyboard commands
	pugi::xml_node commands = doc.child("Commands");

	// Player1
	pugi::xml_node player1 = commands.child("Player1");
	for (pugi::xml_node command1 : player1.children()) { // player1 commands
		std::map<std::string, int> attributes;
		for (pugi::xml_attribute attr : command1.attributes()) {
			attributes[attr.name()] = attr.as_int();
		}
		keyboardCommandsPlayer1[command1.name()] = attributes["code"]; // We get the key code
	}


	// Player2
	pugi::xml_node player2 = commands.child("Player2");
	for (pugi::xml_node command2 : player2.children()) { // player1 commands
		std::map<std::string, int> attributes;
		for (pugi::xml_attribute attr : command2.attributes()) {
			attributes[attr.name()] = attr.as_int();
		}
		keyboardCommandsPlayer2[command2.name()] = attributes["code"]; // We get the key code
	}

	return 0;
}
