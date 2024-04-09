#include "../includes/parsing/config.hpp"
#include "../includes/sockets/WebServer.hpp"

void sigpipeHandler(int signum) {
    (void)signum;
}

int main(int ac, char **av){
    if (ac == 1 || ac == 2) {
        ConfigFile conf;
        try {
            signal(SIGPIPE, sigpipeHandler);
            conf.openConfig();
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
