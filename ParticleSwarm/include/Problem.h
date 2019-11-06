#ifndef PROBLEM_H
#define PROBLEM_H
#include <utility>

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
	
	Problem();

	/*Max distance*/
	virtual double mdist();

	/*p distance (from lab writeup)*/
	virtual double pdist(std::pair<double, double> &p);

	/*n distance (from lab writeup)*/
	virtual double ndist(std::pair<double, double> &p);

	virtual double Q(std::pair<double, double> &p) = 0;

	friend class ParticleSwarmOptimizer;
};

#endif /* PROBLEM_H */