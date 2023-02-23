#include "types.h"
#include "vectormath.h"
#include "physics.h"
#include <math.h>
#include <iostream>

#define ACCEL_SCALE FORCE_SCALE / MASS_SCALE / DISTANCE_SCALE

// Outputs acceleration in 1 million km / s ^ 2
sf::Vector2f calcAccel(Force force, float mass) {
	sf::Vector2f dir = normalize(force.direction);

	return dir * force.magnitude / mass * float(ACCEL_SCALE);
}

// Outputs velocity in 1 million km/s
sf::Vector2f calcVel(sf::Vector2f init, sf::Vector2f accel, float time) {
	return (init + accel * time);
}

// Outputs force in 1 million newton units
float calcGravMag(float mass1, float mass2, float distance) {
	return G * ((mass1 * mass2) / (distance * distance));
}