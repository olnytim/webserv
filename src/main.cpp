#include "../includes/parsing/config.hpp"

int main(){
	ConfigFile conf;
	try{
		conf.openConfig();
		conf.parse();
        conf.printParsing();
	} catch (const ParseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
	}
}
