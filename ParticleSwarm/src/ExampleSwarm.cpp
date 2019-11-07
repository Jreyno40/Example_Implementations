#include <fstream>
#include <iostream>
#include <cstdio>
#include "PSO.h"
#include "Particle.h"
#include "Problem.h"
#include "FunctionOne.h"
#include "FunctionTwo.h"

using namespace std;
using namespace PSO;

constexpr auto OUTPUT = 1;

/*Simulation!*/
int main(int argc, char **argv) {

	FunctionOne* prob = new FunctionOne;
	FunctionTwo* prob2 = new FunctionTwo;
	ParticleSwarmOptimizer PSO(prob2);

	if (OUTPUT) {
		ofstream fout("start_particles.csv");
		fout << "x," << "y" << endl;
		for (int i = 0; i < PSO.data.num_particles; i++) {
			fout << PSO.particles[i]->data.position.first << ", " << PSO.particles[i]->data.position.second << "\n";
		}
		fout.close();
	}

	/*scatter plot of particles + maximum*/
	/*x: epoch y: diff avg vs global*/
	/*x: epoch y: percent converged*/
	ofstream fout1("diff.csv");
	ofstream fout2("percent.csv");
	ofstream fout3("errors.csv");

	fout1 << "epoch," << "diffx," << "diffy" << endl;
	fout2 << "epoch," << "percent" << endl;
	fout3 << "epoch," << "x," << "y" << endl;

	int epoch = 0;
	/*Either the error converges or we complete all epochs*/
	while ((PSO.data.error_x > 0.01 && PSO.data.error_y > 0.01) && (epoch < PSO.data.epochs)) {

		/*Update positions, velocities, bestPosition and g_best*/
		PSO.update_loop();

		/*Compute average error*/
		PSO.avg_error();

		if (OUTPUT)
			fout3 << epoch << ", " << PSO.data.error_x << ", " << PSO.data.error_y << endl;

		pair <double, double> result = PSO.avg_coord_best_coord();

		if (OUTPUT)
			fout1 << epoch << ", " << result.first << ", " << result.second << "\n";
			fout2 << epoch << ", " << PSO.percent_within() << "\n";

		epoch++;
	}

	fout1.close();
	fout2.close();
	fout3.close();

	/*Output particle positions*/
	if (OUTPUT) {
		ofstream fout4("end_particles.csv");
		fout4 << "x," << "y" << endl;
		for (int i = 0; i < PSO.data.num_particles; i++) {
			fout4 << PSO.particles[i]->data.position.first << ", " << PSO.particles[i]->data.position.second << "\n";
		}
		fout4.close();
	}

	printf("Error x: %f y: %f\nBest index fitness: %d %f\nBest Position: %f %f\n", PSO.data.error_x, PSO.data.error_y, PSO.data.best_index, PSO.prob->Q(PSO.g_best), PSO.g_best.first, PSO.g_best.second);

	return 0;
}