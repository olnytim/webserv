#include "../includes/parsing/config.hpp"
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
    for (size_t i = 0; i < conf.servers.size(); ++i){
        std::cout << conf.servers[i].getPort() << std::endl;
        WebServer webserver(conf.servers[i]);
        if (!webserver.init())
            return 1;
        webserver.run();
    }
    return 0;
}
