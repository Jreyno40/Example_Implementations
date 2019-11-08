#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "JSONWrapper.hpp"
#include "Particle.hpp"
#include "PSO.hpp"
#include "Problem.hpp"

using namespace std;

namespace PSO {

	ParticleSwarmOptimizer::ParticleSwarmOptimizer(Problem* func) : prob(func) {

		ParticleData particleData;

		JSONWrapper parameters("params.json");

		vector<string> varList = { "epochs", "num_particles", "error_x",
			"error_y", "seed", "inertia", "cognition", "social",
			"max_velocity", "inertia_decrease" };

		/*Error check for existence*/
		if (!parameters.CheckExistence(varList)) {
			cerr << "A required parameter is missing." << endl;
			cerr.flush();
			exit(1);
		}

		data.epochs = parameters.data["epochs"];
		data.num_particles = parameters.data["num_particles"];
		data.error_x = parameters.data["error_x"];
		data.error_y = parameters.data["error_y"];
		//data.g_fit = 0;
		data.best_index = 0;

		srand(parameters.data["seed"]);

		particleData.inertia = parameters.data["inertia"];
		particleData.cognition = parameters.data["cognition"];
		particleData.social = parameters.data["social"];
		particleData.max_velocity = parameters.data["max_velocity"];
		particleData.inertia_decrease = parameters.data["inertia_decrease"];

		init_particles(particleData);

	}

	/*Initialize the particles*/
	pair<int, double> ParticleSwarmOptimizer::init_particles(ParticleData particleData) {
		for (int i = 0; i < data.num_particles; i++) {

			double tmp = rand() % prob->width + 1;
			tmp *= rand() % 2 == 1 ? 1 : -1;

			double tmp2 = rand() % prob->height + 1;
			tmp2 *= rand() % 2 == 1 ? 1 : -1;

			particleData.position = std::make_pair(tmp, tmp2);
			particles.push_back(new Particle(particleData));
		}

		return init_fit();
	}

	/*Compute fitness values, set initial global best*/
	pair<int, double> ParticleSwarmOptimizer::init_fit() {
		double max = 0;
		for (int i = 0; i < data.num_particles; i++) {
			particles[i]->data.fitness = prob->Q(particles[i]->data.position);

			if (particles[i]->data.fitness > max) {
				max = particles[i]->data.fitness;
				g_best = particles[i]->data.position;
				//data.g_fit = max;
				data.best_index = i;
			}
		}
		return make_pair(data.best_index, max);
	}

	/*Check and see if we need to update p_best*/
	void ParticleSwarmOptimizer::p_best_check(Particle *p) {
		if (prob->Q(p->data.position) > prob->Q(p->data.bestPosition))
			p->data.bestPosition = p->data.position;
	}

	/*update global best?*/
	void ParticleSwarmOptimizer::g_best_check(int &index, Particle *p) {
		if (prob->Q(p->data.position) > prob->Q(g_best)) {
			g_best = p->data.position;
			data.best_index = index;
		}
	}

	/*Compute the average error*/
	void ParticleSwarmOptimizer::avg_error() {
		double err_x = 0, err_y = 0;

		for (int i = 0; i < data.num_particles; i++) {
			err_x += pow(particles[i]->data.position.first - g_best.first, 2);
			err_y += pow(particles[i]->data.position.second - g_best.second, 2);
		}

		data.error_x = sqrt((1.0 / (2 * data.num_particles))* err_x);
		data.error_y = sqrt((1.0 / (2 * data.num_particles))* err_y);
	}

	/*diff of avg vs. best coords*/
	pair <double, double> ParticleSwarmOptimizer::avg_coord_best_coord() {

		double x = 0, y = 0;

		for (int i = 0; i < data.num_particles; i++) {
			x += particles[i]->data.position.first;
			y += particles[i]->data.position.second;
		}

		x /= data.num_particles;
		y /= data.num_particles;

		return make_pair(x - g_best.first, y - g_best.second);
	}

	/*Update particle velocities and positions*/
	/*Also update personal bests and global best*/
	void ParticleSwarmOptimizer::update_loop() {

		for (int i = 0; i < data.num_particles; i++) {
			particles[i]->velocity_update(g_best);
			particles[i]->position_update();
			p_best_check(particles[i]);
			g_best_check(i, particles[i]);
		}
	}

	double ParticleSwarmOptimizer::percent_within() {

		int count = 0;

		for (int i = 0; i < data.num_particles; i++) {
			double result = prob->pdist(particles[i]->data.position);

			if (result < 1)
				count++;
		}

		return count / (double)data.num_particles;
	}

}