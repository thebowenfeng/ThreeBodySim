# ThreeBodySim

A simple numerical approximation that simulates orbit trajectories of planets in a N-body system.

![Alt Text](demo.gif)

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

## Project rationale

This project is inspired by the [Three Body Problem novel](https://en.wikipedia.org/wiki/The_Three-Body_Problem_(novel)). In the novel, an alien civilisation invades
earth because their planet orbits a system comprised of three stars (three-body system). The aliens wish to predict their home planet's orbital trajectory but was unable to do so because three body problem (i.e formulating a general equation for a three body system) is unsolvable, thus they chose to invade earth.

That being said, it is possible to numerically approximate the orbital trajectories of a three body system using Newton's laws of motion. Given enough data and a powerful enough computer, one is able to predict planet movement even in an inherently chaotic system such as a three body system. This project is a very simplified example of such numerical approximation.

## Non deterministic results and margins of error.

The project uses a very large time interval to numerically approximate movement (default is 1s IRL = 1 month in sim). Because of this, there is a error margin, since the calculation is only ran "once per month" in the simulated world.

The project also relies on measuring CPU execution speeds in order to provide a smoother experience, and also providing a consistent time scale when rendering. Due to variations in CPU clock speed and OS scheduling (and a multitude of other reasons), each iteration of calculations will use a different time unit to calculate velocity/displacement. Coupled with the margins of error discussed above, this can result in variations of simulated trajectories over a longer period of time.
