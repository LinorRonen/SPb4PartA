#pragma once
#include <vector>
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include <memory>
using namespace std;

namespace ariel {

    class Team {

    private:

        std::vector<Character*> members;

        Character* leader;

    public:

        //Constructor
        Team(Character* leader);

        //Destructor
        virtual ~Team();

        // Copy constructor
        Team(const Team& other);

        // Copy assignment operator
        Team& operator=(const Team& other);

        //Move constructor
        Team(Team&& other) noexcept;

        //Move assignment operator
        Team& operator=(Team&& other) noexcept;

        //Add a member to the team
        void add(Character* member);

        //Check if any members of the team are still alive
        int stillAlive() const;

        //attack()
        virtual void attack(Team *other);

        //print()
        virtual void print() const;

        //Get the leader character of the team
        Character* getLeader() const { return leader; }

        //Get the vector of members in the team
        const std::vector<Character*>& getMembers() const { return members;}
 
    };

    // Team2 class derived from Team
    class Team2 : public Team {

    public:

    //Constructor
    Team2(Character* leader);

    void attack(Team *other) override;

    void print() const override;
};

// SmartTeam class derived from Team
class SmartTeam : public Team {

public:

    //Constructor
    SmartTeam(Character* leader);

    void attack(Team *other) override;

    void print() const override;
};
}
