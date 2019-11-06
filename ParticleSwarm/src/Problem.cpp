#include "json.hpp"
#include "Problem.h"
#include <utility>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Problem::Problem() {
	json j;

	{
		std::ifstream fin("params.json");
		if (fin.fail()) {
			std::cerr << "Error: file \"params.json\" does not exist." << std::endl;
			std::cerr.flush();
			exit(1);
		}

		try {
			j = json::parse(fin);
		}
		catch (json::exception& e) {
			std::cerr << e.what() << std::endl;
			std::cerr.flush();
			exit(1);
		}

		fin.close();
	}

	if (!j["w_width"].is_number() ||
		!j["w_height"].is_number())
	{
		std::cerr << "A required parameter is missing." << std::endl;
		std::cerr.flush();
		exit(1);
	}

	width = j["w_width"];
	height = j["w_height"];
}

double Problem::mdist() {
	return sqrt(pow(width * 2, 2) + pow(height * 2, 2)) / 2.0;
}

double Problem::pdist(std::pair<double, double> &p) {
	return sqrt(pow(p.first - 20, 2) + pow(p.second - 7, 2));
}

double Problem::ndist(std::pair<double, double> &p) {
	return sqrt(pow(p.first + 20, 2) + pow(p.second + 7, 2));
}