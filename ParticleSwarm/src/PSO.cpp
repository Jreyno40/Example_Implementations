#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Particle.h"
#include "PSO.h"
#include "Problem.h"

using namespace std;
using json = nlohmann::json;

namespace PSO {

	ParticleSwarmOptimizer::ParticleSwarmOptimizer(Problem* func) : prob(func) {

		ParticleData particleData;

		/*Load the parameters*/
		json j;

		{
			ifstream fin("params.json");
			if (fin.fail()) {
				cerr << "Error: file \"params.json\" does not exist." << endl;
				cerr.flush();
				exit(1);
			}

			try {
				j = json::parse(fin);
			}
			catch (json::exception& e) {
				cerr << e.what() << endl;
				cerr.flush();
				exit(1);
			}

			fin.close();
		}

		/*Error check for existence*/
		{
			if (!j["epochs"].is_number() ||
				!j["num_particles"].is_number() ||
				!j["error_x"].is_number() ||
				!j["error_y"].is_number() ||
				!j["seed"].is_number() ||
				!j["inertia"].is_number() ||
				!j["cognition"].is_number() ||
				!j["social"].is_number() ||
				!j["max_velocity"].is_number() ||
				!j["inertia_decrease"].is_number())
			{
				cerr << "A required parameter is missing." << endl;
				cerr.flush();
				exit(1);
			}
		}


		data.epochs = j["epochs"];
		data.num_particles = j["num_particles"];
		data.error_x = j["error_x"];
		data.error_y = j["error_y"];
		data.g_fit = 0;
		data.best_index = 0;

		srand(j["seed"]);

		particleData.inertia = j["inertia"];
		particleData.cognition = j["cognition"];
		particleData.social = j["social"];
		particleData.max_velocity = j["max_velocity"];
		particleData.inertia_decrease = j["inertia_decrease"];


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
				data.g_fit = max;
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