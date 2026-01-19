#include <iostream> // For error logging and status messages
#include "../include/config/ConfigParser.hpp"
#include "../include/config/ConfigStructs.hpp"

int main(int argc, char **argv)
{
	if (argc > 2) {
		std::cerr << "Usage: ./webserv [config_file]" << std::endl;
		return 1;
	}
	std::string configPath = (argc == 2) ? argv[1] : "../default.conf";
	try
	{
		//Partner A
		Config parser;
		parser.parse(configPath);
		std::vector<ServerConfig> configs = parser.getConfigs();
		// Partner B
		std::vector<TcpListener> listeners;
		for (size_t i = 0; i < configs.size(); ++i) {
			TcpListener server(configs[i]);
			server.init();
			listeners.push_back(server);
		}

		// Next step: The Poll Loop (Coming soon...)
	}
	catch(const std::exception& e)
	{
		std::cerr  << "Error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
