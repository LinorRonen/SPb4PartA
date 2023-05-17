#pragma once

#include <string>
#include "Point.hpp"

namespace ariel {

    class Character {
    
    private:

        // The character's location
        Point& location; 

        // The character's hit points
        int hit_points;

        // The character's name
        std::string name;

    public:
    
        // Constructor
        Character(std::string name, Point& loc, int hit_points);

        // Copy constructor
        Character(const Character& other);

        // Copy assignment operator
        Character& operator=(const Character& other);

        // Move constructor
        Character(Character&& other) noexcept;

        // Move assignment operator
        Character& operator=(Character&& other) noexcept;

        // Destructor
        virtual ~Character() {}

        // Check if the character is alive
        bool isAlive() const;

        // Calculate the distance between this character and another character
        double distance(const Character* other) const;

        //Subtracts the appropriate amount of hit points from the character.
        void hit(int num);

        // Get the character's name
        std::string getName() const;

        // Get the character's hit points
        int getHitPoints() const;

        // Get the character's location
        Point& getLocation() const;

        // Set the character's location
        void setLocation(const Point& newLoc);
        
        // Pure virtual function for printing character information
        virtual std::string print() const = 0;
    };

}  
