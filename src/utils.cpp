#include "utils.h"

void loge(std::string lg , std::string ms ){
	std::cout << "[" << lg << "] " << ms << ".\n";
	return;
}
void Eloge(std::string ms){
	 std::cerr << "[ERORR] " << ms << ".\n";
}
void Wloge(std::string ms){
	 std::cerr << "[WARNING] " << ms << ".\n";
}

void readFile(std::string path, std::string& data){
	std::ifstream fl(path);
	if(!fl.is_open()){
		Eloge("At opening " + path + " file disnt exiset or curupted");
		return;
	}
	fl.seekg(0,fl.end);
	
	unsigned int u_fileSize = fl.tellg();
	data.resize(u_fileSize);
	
	fl.seekg(0);
	fl.read(data.data(), u_fileSize);
	fl.close();
		
	return;
}
