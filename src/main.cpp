#include "../includes/parsing/config.hpp"
#include "../includes/request/RequestParsing.hpp"

int main(int argc, char **argv){
	ConfigFile conf;
	Request req;
	RequestParsing reqp(req);

	try{
		switch (argc){
			case 1:
				conf.openConfig("test.conf");
				break;
			case 2:
				conf.openConfig(argv[1]);
				break;
			default:
				return (1);
		}
		conf.parse();
		// conf.printParsing();
		reqp.parse(argv[1]);
	} catch (const ParseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
	}
}
