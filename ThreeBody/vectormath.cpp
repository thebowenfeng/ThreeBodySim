#include<math.h>
#include "vectormath.h"
#include <SFML/System/Vector2.hpp>

float length(sf::Vector2f vec) {
	double x = double(vec.x);
	double y = double(vec.y);

	return float(sqrt(x * x + y * y));
}

float posNeg(float num) {
	if (num > 0) {
		return 1;
	}
	else {
		return -1;
	}
}

sf::Vector2f normalize(sf::Vector2f vec) {
	if (vec.x != 0.f && vec.y == 0.f) {
		return { posNeg(vec.x), 0};
	}
	else if (vec.x == 0.f && vec.y != 0.f) {
		return { 0, posNeg(vec.y) };
	}

	float len = length(vec);
	if (len == 0.f) return { 0, 0 };

	return vec / len;
}