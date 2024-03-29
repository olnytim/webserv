#include "../includes/parsing/config.hpp"
#include "../includes/request/Request.hpp"

int main(int argc, char **argv){
	ConfigFile conf;
	Request req;
	(void)argc;
	try{
		conf.openConfig();
		conf.parse();
        // conf.printParsing();
	} catch (const ParseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	req.parse(argv[1]);
}
