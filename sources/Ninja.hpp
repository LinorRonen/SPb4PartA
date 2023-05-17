#pragma once

#include "Character.hpp"

namespace ariel {

    // Ninja class derived from Character
    class Ninja : public Character {

    private:
        //the speed 
        int speed;

    public:

        // Constructor
        Ninja(std::string name, const Point& loc, int hpoints, int speed);

        //move()
        void move(Character* enemy);

        //slash()
        void slash(Character* enemy);

        // Get the speed of the ninja
        int getSpeed() const;

        // Print() (override)
        std::string print() const override;
    };

    // YoungNinja class derived from Ninja
    class YoungNinja : public Ninja {

    public:

        // Constructor
        YoungNinja(std::string name, const Point& loc);

        //print()
        std::string print() const override;

    };

    // TrainedNinja class derived from Ninja
    class TrainedNinja : public Ninja {

    public:

        // Constructor
        TrainedNinja(std::string name, const Point& loc);

        //print()
        std::string print() const override;
    };

    // OldNinja class derived from Ninja
    class OldNinja : public Ninja {

    public:

        // Constructor
        OldNinja(std::string name, const Point& loc);

        //print()
        std::string print() const override;

    };

}
