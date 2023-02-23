#include <SFML/Graphics.hpp>
#include "types.h"
#include "physics.h"
#include "vectormath.h"
#include <iostream>
#include <Windows.h>
#include <chrono>

#define TIME_SCALE 3600 * 24 * 5 // 1 second IRL = 1 month in sim

void render(sf::RenderWindow* window, std::vector<Planet*> planets) {
    for (Planet* planet : planets) {
        window->draw(planet->shape);
    }
}

void updatePos(std::vector<Planet*> planets, float time) {
    for (Planet* planet : planets) {
        planet->changePos(time);
    }
}

std::vector<Force> calcForces(std::vector<Planet*> planets) {
    // Initialize empty list of forces, index corresponding to each planet
    std::vector<std::vector<Force>> allForces;
    for (int i = 0; i < planets.size(); i++) allForces.push_back({});

    std::vector<Force> res;

    // Calculate force exerted on each planet
    for (int i = 0; i < planets.size(); i++) {
        Planet* planet1 = planets[i];

        for (int j = i + 1; j < planets.size(); j++) {
            Planet* planet2 = planets[j];

            float mutualF = calcGravMag(planet1->mass, planet2->mass, length(planet1->shape.getPosition() - planet2->shape.getPosition()));
            Force forceOn1 = { normalize(planet2->shape.getPosition() - planet1->shape.getPosition()), mutualF };
            Force forceOn2 = { normalize(planet1->shape.getPosition() - planet2->shape.getPosition()), mutualF };

            allForces[i].push_back(forceOn1);
            allForces[j].push_back(forceOn2);
        }
    }

    // Aggregate force on each planet
    for (std::vector<Force> forces : allForces) {
        sf::Vector2f aggre = { 0.f, 0.f };

        for (Force force : forces) {
            aggre += force.direction * force.magnitude;
        }

        sf::Vector2f aggreDir = normalize(aggre);
        float aggreMag = length(aggre);

        res.push_back(Force{ aggreDir, aggreMag });
    }

    return res;
}

void updateVel(std::vector<Planet*> planets, std::vector<Force> forces, float time) {
    for (int i = 0; i < planets.size(); i++) {
        Planet* planet = planets[i];

        planet->vel = calcVel(planet->vel, calcAccel(forces[i], planet->mass), time);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setVerticalSyncEnabled(true);

    // Initialize planets here
    // Make sure to add each planet by reference into the "planets" array
    Planet sun1({ 0, 0 }, 1.989 * powf(10, 6), 5.f, {300, 300});
    Planet sun2({ 25.f / 1000000, 0 }, 1.989 * powf(10, 6), 5.f, { 300, 150 });
    Planet sun3({ -25.f / 1000000, 0 }, 1.989 * powf(10, 6), 5.f, { 300, 450 });
    Planet planet1({ -25.f / 1000000, 0 }, 1.989, 2.f, { 300, 600 }, sf::Color::Green);

    std::vector<Planet*> planets = { &sun1, &sun2, &sun3, &planet1 };

    float TIME_PER_FRAME = 0.001f;
    //int counter = 0;

    sf::Texture frame;
    frame.create(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        auto begin = std::chrono::high_resolution_clock::now();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } 
        }

        updateVel(planets, calcForces(planets), TIME_PER_FRAME * TIME_SCALE);
        updatePos(planets, TIME_PER_FRAME * TIME_SCALE);

        window.clear();
        render(&window, planets);
        window.display();

        //frame.update(window);
        //frame.copyToImage().saveToFile(std::to_string(counter) + ".jpg");
        //counter ++;

        auto end = std::chrono::high_resolution_clock::now();
        TIME_PER_FRAME = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * pow(10, -9);
    }

    return 0;
}