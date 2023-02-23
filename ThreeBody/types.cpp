#include "types.h"

Planet::Planet(sf::Vector2f initVel, float _mass, float radius, sf::Vector2f initPos, sf::Color color) {
	vel = initVel;
	mass = _mass;

	shape = sf::CircleShape(radius);
	shape.setFillColor(color);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(initPos);
}

void Planet::changePos(float time) {
	shape.setPosition(shape.getPosition() + vel * time);
}