#include "config.hpp"

int main(){
	configFile conf;
	try{
		conf.openConfig();
		conf.parse();
	} catch (const parseException &ex){
		std::cerr << "Error: " << ex.what() << std::endl;
	}
}
