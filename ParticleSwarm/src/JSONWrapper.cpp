#include "JSONWrapper.hpp"
#include <fstream>
#include <iostream>

JSONWrapper::JSONWrapper(std::string filename) {

	std::ifstream fin(filename);

	if (fin.fail()) {
		std::cerr << "Error: file \"params.json\" does not exist." << std::endl;
		std::cerr.flush();
		exit(1);
	}

	try {
		data = json::parse(fin);
	}
	catch (json::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cerr.flush();
		exit(1);
	}

	fin.close();
}

bool JSONWrapper::CheckExistence(std::vector<std::string>& parameters) {

	for (auto it = parameters.begin(); it != parameters.end(); it++) {
		if (!data[*it].is_number())
		{	
			return false;
		}
	}

	return true;
}