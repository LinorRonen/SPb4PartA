#include "Ninja.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace ariel;

// Constructor - Ninja
Ninja::Ninja(string name, const Point& loc, int hp, int spd): Character(name, const_cast<Point&>(loc), hp), speed(spd) {}

//move()
void Ninja::move(Character* enemy) 
{
    Point enemyLoc = enemy->getLocation();
    setLocation(Point::moveTowards(getLocation(), enemyLoc, speed));
    std::cout << getName() << " moved towards " << enemy->getName() << std::endl; 
}

//slash()
void Ninja::slash(Character* enemy) 
{
    
    if (enemy != nullptr && isAlive() && getLocation().distance(enemy->getLocation()) <= 1) {
        std::cout << getName() << " slashes at " << enemy->getName() << std::endl;
        enemy->hit(40);
    }
    
}

//print() - Ninja
std::string Ninja::print() const 
{
    std::string str = "Ninja: " + getName() + " (" + std::to_string(getHitPoints()) + "), Speed: " + std::to_string(speed) + ", Location: ";
    str += getLocation().print();
    return str;
}

//Constructor - YoungNinja
YoungNinja::YoungNinja(string name, const Point& loc): Ninja(name, const_cast<Point&>(loc), 100, 14) {}

//print() - YoungNinja
std::string YoungNinja::print() const 
{
    std::string str;
    if (isAlive()) {
        str = "N: " + getName() + " (" + std::to_string(getHitPoints()) + "), Speed: " + std::to_string(getSpeed()) + ", Location: ";
        str += getLocation().print();
    } else {
        str = "N: (" + std::to_string(getHitPoints()) + " hit points) {DEAD}";
    }
    return str;
}

//Constructor - TrainedNinja
TrainedNinja::TrainedNinja(string name, const Point& loc): Ninja(name,const_cast<Point&>(loc), 120, 12) {}

//print() - TrainedNinja
std::string TrainedNinja::print() const 
{
    std::string str;
    if (isAlive()) {
        str = "N: " + getName() + " (" + std::to_string(getHitPoints()) + "), Speed: " + std::to_string(getSpeed()) + ", Location: ";
        str += getLocation().print();
    } else {
        str = "N: (" + std::to_string(getHitPoints()) + " hit points) {DEAD}";
    }
    return str;
}

//Constructor - OldNinja
OldNinja::OldNinja(string name, const Point& loc): Ninja(name, const_cast<Point&>(loc), 150, 8) {}

//print() - OldNinja
std::string OldNinja::print() const 
{
    std::string str;
    if (isAlive()) {
        str = "N: " + getName() + " (" + std::to_string(getHitPoints()) + "), Speed: " + std::to_string(getSpeed()) + ", Location: ";
        str += getLocation().print();
    } 
    else 
    {
        str = "N: (" + std::to_string(getHitPoints()) + " hit points) {DEAD}";
    }
    return str;
}

//getSpeed()
int Ninja::getSpeed() const 
{
    return speed;
}


