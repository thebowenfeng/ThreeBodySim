#pragma once
#include <SFML/Graphics.hpp>

class Planet {
public:
	sf::CircleShape shape;
	sf::Vector2f vel;
	float mass;
	Planet(sf::Vector2f, float, float, sf::Vector2f, sf::Color = sf::Color::Red);
	void changePos(float time);
};

typedef struct Force {
	sf::Vector2f direction;
	float magnitude;
} Force;
