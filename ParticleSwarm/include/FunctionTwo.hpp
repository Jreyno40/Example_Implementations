#ifndef FUNCTIONTWO_H
#define FUNCTIONTWO_H
#include "Problem.hpp"
#include <cmath>
#include <algorithm>

namespace PSO {

	/**
	* @class FunctionTwo
	* @brief This inherits from the Problem interface to define a sample problem.
	*/
	class FunctionTwo : public Problem {

		/**
		* This function returns the ndist. It is unique to FunctionTwo.
		* @return nDistance Arbitrary distance for a problem to be optimized.
		*/
		double ndist(const std::pair<double, double> &p) {
			return sqrt(pow(p.first + 20, 2) + pow(p.second + 7, 2));
		}


	public:

		double Q(const std::pair<double, double> &p) {
			return 9.0 * std::max(0.0, 10 - pow(pdist(p), 2)) +
				10 * (1 - (pdist(p) / mdist())) + 70 * (1 - (ndist(p) / mdist()));
		}

	};

}

#endif /* FUNCTIONTWO_H */
