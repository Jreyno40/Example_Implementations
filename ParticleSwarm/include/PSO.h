#ifndef PSO_H
#define PSO_H
#include <vector>
#include <utility>

class Particle;
class Problem;
struct ParticleData;

/**
* @struct PSOData
* @brief This is pure data stored by the PSO class.
*/
struct PSOData {
	int num_particles;
	int epochs;
	int best_index;
	double g_fit;
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
class ParticleSwarmOptimizer{

	std::pair<int, double> init_fit();
	void p_best_check(Particle *p);
	void g_best_check(int &index, Particle *p);

public:

	Problem *prob;
	ParticleSwarmOptimizer(Problem* func);

	std::pair<int, double> init_particles(ParticleData data);
	std::pair<double, double> avg_coord_best_coord();
	void avg_error();
	void update_loop();
	double percent_within();

	std::vector <Particle *> particles;
	std::pair <double, double> g_best;

	PSOData data;
};

#endif /* PSO_H */