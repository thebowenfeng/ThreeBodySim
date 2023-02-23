#pragma once
#include <SFML/System/Vector2.hpp>

#define MASS_SCALE powf(10, 24) // 10^20 kg
#define DISTANCE_SCALE 1000000000 // 1 million km (1 billion m)
#define FORCE_SCALE 10000000000000000 // 10 ^ 16 newtons
#define G 6.6743 * powf(10, -11) * MASS_SCALE * MASS_SCALE / DISTANCE_SCALE / DISTANCE_SCALE / FORCE_SCALE

sf::Vector2f calcAccel(Force force, float mass);

sf::Vector2f calcVel(sf::Vector2f init, sf::Vector2f accel, float time);

float calcGravMag(float mass1, float mass2, float distance);
