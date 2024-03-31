#include "../includes/parsing/config.hpp"
#include "../includes/parsing/ServerBlock.hpp"
#include "../includes/parsing/LocationBlock.hpp"
#include "../includes/sockets/Webserv.hpp"

int main(){
	ConfigFile conf;
	try{
		conf.openConfig();
		conf.parse();
        conf.printParsing();

	} catch (const ParseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
	}
    ServerBlock server;
    Webserv webserver(server);
    webserver.run();
    return 0;
}
