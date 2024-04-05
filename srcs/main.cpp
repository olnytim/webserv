#include "../includes/parsing/config.hpp"
#include "../includes/parsing/ServerBlock.hpp"
#include "../includes/parsing/LocationBlock.hpp"
#include "../includes/sockets/WebServer.hpp"

int main(){
	ConfigFile conf;
	try{
		conf.openConfig();
		conf.parse();
        conf.printParsing();
	} catch (const ParseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
	}
//    for (size_t i = 0; i < conf.servers.size(); ++i){
//        std::cout << conf.servers[i].getPort() << std::endl;
//        Webserv webserver(conf.servers[i]);
//        webserver.run();
//    }
	WebServer server(8080, "0.0.0.0");
	if (!server.init())
		return 1;
	server.run();
    return 0;
}
