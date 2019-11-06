#include "Particle.h"
#include "json.hpp"
#include <utility>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

constexpr auto GRAD = 0;

Particle::Particle(ParticleData data): data(data) {
	data.bestPosition = data.position;
	data.velocity = std::make_pair(0, 0);
	data.fitness = 0;
}

void Particle::position_update() {
	data.position.first = data.position.first + data.velocity.first;
	data.position.second = data.position.second + data.velocity.second;
}

void Particle::velocity_update(std::pair <double, double> g_best) {

	data.velocity.first = data.inertia * data.velocity.first + data.cognition * 
		rand() / RAND_MAX * (data.bestPosition.first - data.position.first) + 
		data.social * rand() / RAND_MAX * (g_best.first - data.position.first);

	data.velocity.second = data.inertia * data.velocity.second + data.cognition *
		rand() / RAND_MAX * (data.bestPosition.second - data.position.second) + 
		data.social * rand() / RAND_MAX * (g_best.second - data.position.second);

	/*Scale velocity*/
	if ((pow(data.velocity.first, 2) + pow(data.velocity.second, 2)) > pow(data.max_velocity, 2)) {

		data.velocity.first = (data.max_velocity / sqrt(pow(data.velocity.first, 2) +
			pow(data.velocity.second, 2))) * data.velocity.first;

		data.velocity.second = (data.max_velocity / sqrt(pow(data.velocity.first, 2) +
			pow(data.velocity.second, 2))) * data.velocity.second;

	}

	if (GRAD) {
		data.inertia -= data.inertia * data.inertia_decrease;
	}
}