#include "JSONWrapper.hpp"
#include "Problem.hpp"
#include <utility>
#include <fstream>
#include <iostream>

using namespace std;

namespace PSO {

	Problem::Problem() {

		JSONWrapper parameters("params.json");

		vector<string> varList = { "w_width", "w_height" };

		if (!parameters.CheckExistence(varList))
		{
			std::cerr << "A required parameter is missing." << std::endl;
			std::cerr.flush();
			exit(1);
		}

		width = parameters.data["w_width"];
		height = parameters.data["w_height"];
	}

	double Problem::mdist() {
		return sqrt(pow(width * 2, 2) + pow(height * 2, 2)) / 2.0;
	}

	double Problem::pdist(std::pair<double, double> &p) {
		return sqrt(pow(p.first - 20, 2) + pow(p.second - 7, 2));
	}

}