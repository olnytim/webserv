#include "../includes/config.hpp"

int main(){
	ConfigFile conf;
	try{
		conf.openConfig();
		conf.parse();
	} catch (const ParseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
	}
}
