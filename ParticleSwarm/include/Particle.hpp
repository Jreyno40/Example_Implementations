#ifndef PARTICLE_H
#define PARTICLE_H
#include<utility>

namespace PSO {

	/**
	* @struct ParticleData
	* @brief Data describing individual particle behavior.
	*
	* This can be described as "Plain Old Data", or POD. This means it contains
	* only data that is read/written to and utilized throughout the Particle class.
	*/
	struct ParticleData {

		// The metric defining a particle's success
		double fitness;

		// Inertia describes the resistance to change in velocity
		double inertia;
		
		// "The cognitive parameter controls the experience influence of each 
		// particle with respect to its best performance found so far, while 
		// the social parameter with respect to the best position found by its 
		// society, i.e. either the whole swarm or its neighborhood."
		// Quote from M.G.Epitropakis, V.P.Plagianakos, M.N.Vrahatis
		// - https://doi.org/10.1016/j.ins.2012.05.017
		double cognition;
		double social;
		
		// Maximum velocity value
		double max_velocity;
		
		// The percentage by which inertia decreases per epoch
		double inertia_decrease;

		// Current particle position
		std::pair<double, double> position;
		
		// Current particle velocity
		std::pair<double, double> velocity;
		
		// The recorded best position discovered in the particle's lifetime
		std::pair<double, double> bestPosition;

	};

	/**
	* @class Particle
	* @brief These are Particles for use with Particle Swarm Optimization.
	*
	* Particle Swarm Optimization (PSO) is a non-gradient based optimization
	* technique for iteratively improving candidate solutions towards a target
	* solution. The term "particle" refers to a candidate solution. Decoupling the
	* particle definition from the function to be optimized allows for the
	* ParticleSwarmOptimizer class to manage the particle simulation (velocity,
	* position, intertia, etc.) without concern for the given problem.
	* Wikipedia provides a comprehensive description of PSO.
	*/
	class Particle {

	public:

		// Instance of the struct defined above for holding data
		ParticleData data;
		
		/**
		* The Particle constructor takes a data struct, modifies it, and stores 
		* it internally.
		*/
		Particle(ParticleData data);

	protected:

		/**
		* Updates the particle position
		*/
		void position_update();
		
		/**
		* Updates the particle velocity
		*/
		void velocity_update(std::pair <double, double> g_best);

		friend class ParticleSwarmOptimizer;
	};

}

#endif /* PARTICLE_H */