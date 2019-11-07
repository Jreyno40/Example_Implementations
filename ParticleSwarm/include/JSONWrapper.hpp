#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H
#include "json.hpp"
#include <string>

using json = nlohmann::json;

class JSONWrapper {

public:
	json data;
	JSONWrapper(std::string filename);

	bool CheckExistence(std::vector<std::string>& parameters);
};

#endif /* JSONWRAPPER_H */