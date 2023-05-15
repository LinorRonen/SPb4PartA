#include "Character.hpp"
#include <stdexcept>

namespace ariel {

    // Constructor
    Character::Character(std::string name, Point& loc, int hit_points): location(loc), hit_points(hit_points), name(name){}
    
    // Copy constructor
    Character::Character(const Character& other): location(other.location), hit_points(other.hit_points), name(other.name){}

    // Copy assignment operator
    Character& Character::operator=(const Character& other)
    {
        if (this != &other) {
            hit_points = other.hit_points;
            name = other.name;
        }
        return *this;
    }

    // Move constructor
    Character::Character(Character&& other) noexcept: location(other.location), hit_points(other.hit_points), name(std::move(other.name))
    {
        other.hit_points = 0;
    }

    // Move assignment operator
    Character& Character::operator=(Character&& other) noexcept
    {
        if (this != &other) {
            hit_points = other.hit_points;
            name = std::move(other.name);
            other.hit_points = 0;
        }
        return *this;
    }

    //isAlive()
    bool Character::isAlive() const
    {
        return this->hit_points > 0;
    }

    //distance()
    double Character::distance(const Character* other) const 
    {
        if (other == nullptr) 
        {
            throw std::invalid_argument("Invalid pointer to Character.");
        }
        return location.distance(other->location);
    }

    // Reduce the character's hit points by the specified amount
    void Character::hit(int num)
    {
        this->hit_points -= num;
        if (hit_points < 0) 
        {
            hit_points = 0;
        }
    }

    // Get the name of the character
    std::string Character::getName() const
    {
        return this->name;
    }

    //getHitPoints()
    int Character::getHitPoints() const
    {
        return this->hit_points;
    }

    //getLocation()
    Point& Character::getLocation() const
    {
        return location;
    }

    //setLocation()
    void Character::setLocation(const Point& newLoc) 
    {
        this->location = newLoc;
    }

}  
