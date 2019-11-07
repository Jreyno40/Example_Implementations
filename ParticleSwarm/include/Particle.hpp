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

		/**
		* @param fitness The fitness value defines success for a given candidate
		* solution. This parameter may be useful for external classes, thus public.
		*/
		double fitness;

		double inertia;
		double cognition;
		double social;
		double max_velocity;
		double inertia_decrease;

		std::pair<double, double> position;
		std::pair<double, double> velocity;
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

		ParticleData data;
		Particle(ParticleData data);

	protected:

		void position_update();
		void velocity_update(std::pair <double, double> g_best);

		friend class ParticleSwarmOptimizer;
	};

}

#endif /* PARTICLE_H */