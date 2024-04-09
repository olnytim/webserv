#include "../includes/parsing/config.hpp"
#include "../includes/sockets/WebServer.hpp"

void sigpipeHandler(int signum) {
    (void)signum;
}

int main(int ac, char **av){
    if (ac < 3) {
        ConfigFile conf;
        try {
            signal(SIGPIPE, sigpipeHandler);
            switch (ac){
			case 1:
				conf.openConfig("test.conf");
				break;
			case 2:
				conf.openConfig(av[1]);
				break;
		}
            conf.parse();
            conf.printParsing();
        } catch (const ParseException &ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
            return 1;
        }
        for (size_t i = 0; i < conf.servers.size(); ++i) {
            std::cout << conf.servers[i].getPort() << std::endl;
            WebServer webserver(conf.servers[i]);
            if (!webserver.init())
                return 1;
            webserver.run();
        }
    }
    else {
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        return 1;
    }
    return 0;
}
