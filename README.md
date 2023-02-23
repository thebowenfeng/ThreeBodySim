# ThreeBodySim

A simple numerical approximation that simulates orbit trajectories of planets in a N-body system.

## Installation

This project uses **SFML** to render graphics. If you are using the provided Visual Studio project file, then see [this](https://www.sfml-dev.org/tutorials/2.5/start-vc.php)
for installation of SFML for VS C++. Otherwise, see [this](https://www.sfml-dev.org/tutorials/2.5/) for installation with other C++ IDEs/platforms.

This project is built using **Visual C++ 15** and **SFML 2.5.1**, so make sure to install corresponding versions or ensure your version is compatible.

The project should work cross-platform, under the assumption that SFML is supported on given platform.

## Documentation

Each planet is represented via the ```Planet``` class. The ```Planet``` class can be constructed via: 
```Planet::Planet(sf::Vector2f initVel, float _mass, float radius, sf::Vector2f initPos, sf::Color color)``` 

```sf::Vector2f``` is SFML's float 2d vector class, and ```sf::Color``` is also SFML's color class. Note that color is by default red, but can be customized via SFML's color class.

After each planet is instantiated, each planet object must be added **by reference** (i.e passing a pointer to that object) into a ```std::vector<Planet*>``` array named "planets".

An example usage is as follows:

```
Planet sun1({ 0, 0 }, 1.989 * powf(10, 6), 5.f, {300, 300});
    Planet sun2({ 25.f / 1000000, 0 }, 1.989 * powf(10, 6), 5.f, { 300, 150 });
    Planet sun3({ -25.f / 1000000, 0 }, 1.989 * powf(10, 6), 5.f, { 300, 450 });
    Planet planet1({ -25.f / 1000000, 0 }, 1.989, 2.f, { 300, 600 }, sf::Color::Green);

    std::vector<Planet*> planets = { &sun1, &sun2, &sun3, &planet1 };
```

Declare these objects outside of the main SFML loop, inside ```int main()```

Note that units used in this program are not SI units in order to avoid number overflow, the units can be found in ```physics.h``` and can be adjusted.
