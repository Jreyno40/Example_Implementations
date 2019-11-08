#ifndef PSO_H
#define PSO_H
#include <vector>
#include <utility>

namespace PSO {

	class Particle;
	class Problem;
	struct ParticleData;

	/**
	* @struct PSOData
	* @brief This is pure data stored by the PSO class.
	*/
	struct PSOData {
		
		// Number of particles in the swarm
		int num_particles;
		
		// Number of epochs to simulate
		int epochs;
		
		// The index containing the current best particle
		int best_index;
		
		// Average error in the x and y directions compared to global best
		double error_x, error_y;
	};

	/**
	* @class ParticleSwarmOptimizer
	* @brief This class implements particle swarm optimization.
	*
	* The ParticleSwarmOptimizer class maintains simulation state at a high level.
	* The information maintained includes a vector of particles, the global best,
	* and the average solution error in both x and y dimensions. The class manages
	* particles from creation, through the simulation update loop, and finally to
	* deletion. It maintains a handle to the given Problem class for optimization,
	* which is used to define fitness for individual particles.
	*/
	class ParticleSwarmOptimizer {

		/**
		 * Initializes the fitness values of all particles.
		 */
		std::pair<int, double> init_fit();

		/**
		* Checks particle p to see if current position is its all-time best.
		* @param p particle to check for relative fitness
		*/
		void p_best_check(Particle *p);

		/**
		* Checks particle p to see if it is the global best position.
		* @param index index of passed in particle
		* @param p particle to check for global success
		*/
		void g_best_check(int &index, Particle *p);

	public:

		// Pointer to a problem instance
		Problem *prob;

		/**
		* Constructor for the PSO engine. Loads JSON data using the JSONWrapper
		* class, initializes particles & fitness values, and copies a problem 
		* instantiation to the internal pointer. Seeds RNG.
		* @param func Any implementation of the Problem interface
		*/
		ParticleSwarmOptimizer(Problem* func);

		/**
		* Initializes particle positions with RNG and calls init_fit.
		* @param data Data containing metrics e.g. inertia, cognition, velocity
		*/
		std::pair<int, double> init_particles(ParticleData data);

		/**
		* Difference between the average coordinate and the best coordinate
		*/
		std::pair<double, double> avg_coord_best_coord();
		
		/**
		* Computes the average error across all particles
		*/
		void avg_error();
		
		/**
		* Updates the actual particle swarm simulation. This function performs
		* velocity and position updates as well as checking for global and 
		* individual best fitnesses.
		*/
		void update_loop();
		
		/**
		* Computes the percentage of particles within a certain fitness.
		*/
		double percent_within();

		// Stores all particles involved in the simulation
		std::vector <Particle *> particles;
		
		// Used to record x, y coordinates of global best position
		std::pair <double, double> g_best;

		// Instance of the data struct defined above
		PSOData data;
	};

}

#endif /* PSO_H */