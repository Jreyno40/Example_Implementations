#ifndef PROBLEM_H
#define PROBLEM_H
#include <utility>

namespace PSO {
	/**
	* @class Problem
	* @brief This is the base abstract class for defining Problems to be optimized.
	*
	* The abstract Problem class allows for defining arbitrary functions for
	* optimization with the ParticleSwarmOptimizer class. By providing a
	* c++ interface, the ParticleSwarmOptimizer does not need to be modified for
	* significant changes in the underlying problem.
	*/
	class Problem {

		int width, height;

	public:

		/**
		* The constructor loads the width and height from params.json.
		*/
		Problem();

		/**
		* This function returns the maximum distance of width and height.
		* @return maxDistance The maximum distance.
		*/
		virtual double mdist();

		/**
		* This function returns the pdist.
		* @return pDistance Arbitrary distance for a problem to be optimized.
		*/
		virtual double pdist(std::pair<double, double> &p);

		/**
		* The Q function represents the total function for optimization. It can
		* incorporate other elements. However, this Q function alone will be called
		* from the Particle Swarm Optimizer class.
		* @return fitness Fitness value for the function to be optimized.
		*/
		virtual double Q(std::pair<double, double> &p) = 0;

		friend class ParticleSwarmOptimizer;
	};

}

#endif /* PROBLEM_H */