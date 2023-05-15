#include "Team.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
using namespace std;

namespace ariel 
{

 // Constructor
 Team::Team(Character* leader) : leader(leader) 
{
        if (leader == nullptr) 
        {
            throw std::invalid_argument("Leader cannot be null");
        }
        members.push_back(leader);
}

// Destructor
Team::~Team() 
{
    for (Character* member : members) 
    {
        delete member;
    }
}

// Copy constructor
 Team::Team(const Team& other) : leader(other.leader)
{
    for (Character* member : other.members) 
    {
        if (Cowboy* cowboy = dynamic_cast<Cowboy*>(member)) 
        {
            Cowboy* clonedCowboy = new Cowboy(*cowboy);
            members.push_back(clonedCowboy);
        } 
        else if (Ninja* ninja = dynamic_cast<Ninja*>(member)) 
        {
            Ninja* clonedNinja = new Ninja(*ninja);
            members.push_back(clonedNinja);
        }
    }
}

// Copy assignment operator
Team& Team::operator=(const Team& other)
{
    if (this != &other) 
    {
        // Delete existing members
        for (Character* member : members) 
        {
            delete member;
        }
        members.clear();

        // Copy leader
        leader = other.leader;

        // Copy members
        for (Character* member : other.members) 
        {
            if (Cowboy* cowboy = dynamic_cast<Cowboy*>(member)) 
            {
                Cowboy* clonedCowboy = new Cowboy(*cowboy);
                members.push_back(clonedCowboy);
            } 
            else if (Ninja* ninja = dynamic_cast<Ninja*>(member)) 
            {
                Ninja* clonedNinja = new Ninja(*ninja);
                members.push_back(clonedNinja);
            }
        }
    }
    return *this;
}

//Move constructor
Team::Team(Team&& other) noexcept : leader(other.leader), members(std::move(other.members))
{
    other.leader = nullptr;
}

//Move assignment operator
Team& Team::operator=(Team&& other) noexcept
{
    if (this != &other) {
        // Delete existing members
        for (Character* member : members) 
        {
            delete member;
        }
        members.clear();

        // Move leader and members
        leader = other.leader;
        members = std::move(other.members);

        other.leader = nullptr;
    }
    return *this;
}

//Add a member to the team
 void Team::add(Character* member)
{
    // Check if the character is already in the group
    for (Character* existingMember : members) 
    {
        if (existingMember == member) 
        {
            throw std::runtime_error("Character already exists in the group.");
        }
    }

    if (members.size() >= 10) 
    {
        throw std::runtime_error("There are already 10 members in the team!");
    }

    members.push_back(member);
}

//stillAlive()
int Team::stillAlive() const
{
    int CharacterAliveCount = 0;
    for (const Character* member : members) 
    {
        if (member->isAlive()) 
        {
            CharacterAliveCount++;
        }
    }
    return CharacterAliveCount;   
}

//attack(Team* enemy) 
void Team::attack(Team* enemy) 
{
    // 1) check if any members of the team are still alive
    if(enemy->stillAlive()==0)
    {
        throw std::runtime_error("There is no any members of the team that are still alive ");
    }

    //  2) Check if the leader of the attacking group is alive
    if ( !(this->leader->isAlive()) ) 
    {
        // Find a new leader from the living characters closest to the dead leader
        double theMinDistance = std::numeric_limits<double>::max();

        Character* theNewLeader = nullptr;

        for (Character* member : members) 
        {
            if (member->isAlive()) 
            {
                double distance = leader->getLocation().distance(member->getLocation());

                if (distance < theMinDistance) 
                {
                    theMinDistance = distance;

                    theNewLeader = member;
                }
            }
        }

        if (theNewLeader == nullptr) 
        {
            // No living characters found to be the new leader
            return;
        }

        leader = theNewLeader;
    }

    // 3) Attack (cowboys first)
    for (Character* member : members) 
    {
        Cowboy* cowboy = dynamic_cast<Cowboy*>(member);

        if (cowboy != nullptr && cowboy->isAlive()) 
        {

            Character* theClosestVictim = nullptr;

            double theClosestDistance = std::numeric_limits<double>::max();

            for (Character* enemyMember : enemy->members) 
            {
                if (enemyMember->isAlive()) 
                {
                    double distance = leader->getLocation().distance(enemyMember->getLocation());

                    if (distance < theClosestDistance) 
                    {
                        theClosestDistance = distance;
                        theClosestVictim = enemyMember;
                    }
                }
            }

            if (theClosestVictim != nullptr) 
            {
                if (cowboy->hasBullets()) 
                {
                    cowboy->shoot(theClosestVictim);
                } else 
                {
                    cowboy->reload();
                }
            }
        }
    }

    // 4) Attack (ninjas second)
    for (Character* member : members) 
    {
        Ninja* ninja = dynamic_cast<Ninja*>(member);

        if (ninja != nullptr && ninja->isAlive()) 
        {
            Character* theClosestVictim = nullptr;

            double theClosestDistance = std::numeric_limits<double>::max();

            for (Character* enemyMember : enemy->members) 
            {
                if (enemyMember->isAlive())
                 {
                    double distance = leader->getLocation().distance(enemyMember->getLocation());

                    if (distance < theClosestDistance) 
                    {
                        theClosestDistance = distance;

                        theClosestVictim = enemyMember;
                    }
                }
            }

            if (theClosestVictim != nullptr) 
            {
                if (ninja->getLocation().distance(theClosestVictim->getLocation()) <= 1) 
                {
                    ninja->slash(theClosestVictim);
                } 
                else 
                {
                    ninja->move(theClosestVictim);
                }
            }
        }
    }
    
}

//print()
void Team::print() const 
{
        
    // Print (cowboys)
    for (Character* member : members) 
    {
        Cowboy* cowboy = dynamic_cast<Cowboy*>(member);

        if (cowboy != nullptr) 
        {
            std::cout << cowboy->print() << std::endl;
        }
    }

    // Print (ninjas)
    for (Character* member : members) 
    {
        Ninja* ninja = dynamic_cast<Ninja*>(member);

        if (ninja != nullptr) 
        {
            std::cout << ninja->print() << std::endl;
        }
    }
    
}

 // Constructor
Team2::Team2(Character* leader) : Team(leader) {}

//attack(Team *other)
void Team2::attack(Team *other) {}

//print()
void Team2::print() const {}

// Constructor
SmartTeam::SmartTeam(Character* leader) : Team(leader) {}

//attack(Team *other) 
void SmartTeam::attack(Team *other) {}

//print()
void SmartTeam::print() const{}

}
