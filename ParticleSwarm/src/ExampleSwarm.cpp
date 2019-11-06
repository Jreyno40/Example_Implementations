#include <fstream>
#include <iostream>
#include <cstdio>
#include "PSO.h"
#include "Particle.h"
#include "Problem.h"
#include "FunctionOne.h"
#include "FunctionTwo.h"

constexpr auto POSITIONS = 1;
constexpr auto DEBUG = 0;

using namespace std;

/*Simulation!*/
int main(int argc, char **argv) {

	FunctionOne* prob = new FunctionOne;
	FunctionTwo* prob2 = new FunctionTwo;
	ParticleSwarmOptimizer PSO(prob2);

	/*Init particles*/
	//pair<int, double> result = PSO.init_particles();
	//printf("Starting best index & fit & position:%d %f x: %f y: %f\n", result.first, result.second, PSO.particles[result.first]->data.position.first, PSO.particles[result.first]->data.position.second);

	/*scatter plot of particles + maximum*/
	/*x: epoch y: diff avg vs global*/
	/*x: epoch y: percent converged*/
	ofstream fout1("diff.csv");
	ofstream fout2("percent.csv");

	int epoch = 0;
	
	/*Either the error converges or we complete all epochs*/
	while ((PSO.error_x > 0.01 && PSO.error_y > 0.01) && (epoch < PSO.epochs)) {

		/*Update positions, velocities, bestPosition and g_best*/
		PSO.update_loop();

		/*Compute average error*/
		PSO.avg_error();

		if (DEBUG)
			printf("Error x: %f y: %f\n", PSO.error_x, PSO.error_y);

		pair <double, double> result = PSO.avg_coord_best_coord();
		
		fout1 << epoch << ", " << result.first << ", " << result.second << "\n";
		fout2 << epoch << ", " << PSO.percent_within() << "\n";

		epoch++;
	}

	fout1.close();
	fout2.close();

	/*Output particle positions*/
	/*if (POSITIONS) {
		ofstream fout("particles.csv");
		for (int i = 0; i < PSO.num_particles; i++) {
			fout << PSO.particles[i]->data.position.first << ", " << PSO.particles[i]->data.position.second << "\n";
		}
		fout.close();
	}*/

	printf("Error x: %f y: %f\nBest index fitness: %d %f\nBest Position: %f %f\n", PSO.error_x, PSO.error_y, PSO.best_index, PSO.prob->Q(PSO.g_best), PSO.g_best.first, PSO.g_best.second);

	return 0;
}