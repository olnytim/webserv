#include "../includes/parsing/config.hpp"
#include "../includes/request/Request.hpp"

int main(int argc, char **argv){
	ConfigFile conf;
	// Request req;
	// RequestParse reqp(req);
	(void)argc;
	try{
		conf.openConfig(argv[1]);
		conf.parse();
        // conf.printParsing();
	} catch (const ParseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
	}

	// req.parse(argv[1]);
}
