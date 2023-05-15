#include "Cowboy.hpp"

namespace ariel {

    // Constructor
    Cowboy::Cowboy(std::string name, const Point& loc)
        : Character(name, const_cast<Point&>(loc), 110), bullets(6) {}

     // Copy constructor
    Cowboy::Cowboy(const Cowboy& other)
        : Character(other), bullets(other.bullets) {}

    // Copy assignment operator
    Cowboy& Cowboy::operator=(const Cowboy& other)
    {
        if (this != &other) {
            Character::operator=(other);
            bullets = other.bullets;
        }
        return *this;
    }

    // Move constructor
    Cowboy::Cowboy(Cowboy&& other) noexcept
        : Character(std::move(other)), bullets(other.bullets)
    {
        other.bullets = 0;
    }

    // Move assignment operator
    Cowboy& Cowboy::operator=(Cowboy&& other) noexcept
    {
        if (this != &other) {
            Character::operator=(std::move(other));
            bullets = other.bullets;
            other.bullets = 0;
        }
        return *this;
    }

    // Destructor
    Cowboy::~Cowboy() {}

    //Gets a pointer to the enemy. If the Cowboy is not dead and has bullets left,
    // the Cowboy shoots the enemy, subtracting 10 hit points from the enemy - and losing 1 bullet. Otherwise, no damage will be done to the enemy.
    void Cowboy::shoot(Character* enemy)
  {
    
    if (this->bullets > 0 && enemy != nullptr && enemy->isAlive())
    {
        std::cout << getName() << " shoots at " << enemy->getName() << std::endl;
        this->bullets--;
        enemy->hit(10); //Subtracts the appropriate amount of hit points from the character.
    } 
    else 
    {
        throw std::runtime_error("No bullets left to shoot!");
    }
    
  }

    // Check if the cowboy has bullets
    bool Cowboy::hasBullets() const
    {
        return bullets > 0;
    }

    // Reload bullets
    void Cowboy::reload()
    {
        bullets = 6;
    }

    // Set the number of bullets
    void Cowboy::setBullets(int num)
    {
        this->bullets = num;
    }

    // Print cowboy information
    std::string Cowboy::print() const
    {
        
        return "Cowboy: " + getName() + ", Hit Points: " + std::to_string(getHitPoints()) + ", Bullets: " + std::to_string(bullets);
        
    }

}
