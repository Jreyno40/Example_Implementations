#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H
#include "json.hpp"
#include <string>

using json = nlohmann::json;

/**
* @class JSONWrapper
* @brief Provides a simple data extraction and error checking object.
*
* The constructor loads json data from the provided filename. The 
* CheckExistence function will check all strings in the vector to see if 
* they are valid numbers / existing parameters in the loaded json data. 
*/
class JSONWrapper {

public:

	//The json object filled by the JSONWrapper constructor
	json data;

	/**
	* Constructor that opens an fstream of filename to load json data.
	* @param filename the name of the json parameters file to open
	*/
	JSONWrapper(const std::string& filename);

	/**
	* CheckExistence checks the json data object for the existence (and typing)
	* of all parameter strings from the provided vector.
	* @param parameters the vector of parameter strings to cross-reference
	*/
	bool CheckExistence(const std::vector<std::string>& parameters);
};

#endif /* JSONWRAPPER_H */