//#include "../includes/parsing/config.hpp"
//#include "../includes/sockets/WebServer.hpp"

#include "../includes/parsing/cluster.hpp"
#include "../includes/sockets/web.hpp"

void sigpipeHandler(int signum) {
    (void)signum;
}

int main(int ac, char **av){
    (void)av;
    if (ac < 3) {
        Config conf;
        WebServer servers;
        try {
            signal(SIGPIPE, sigpipeHandler);
            switch (ac) {
                case 1:
                    conf.createCluster("test.conf");
                    break;
                case 2:
                    conf.createCluster(av[1]);
                    break;
            }
//            conf.print();
            servers.setupServers(conf.getServers());
            servers.runServers();
        }
        catch (const ParseException &ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        return 1;
    }
    return 0;
}
