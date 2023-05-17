#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>
using namespace std;

#include "sources/Team.hpp"

using namespace ariel;

// -----------------Point-------------------

TEST_CASE("Point constructor and getters.")
{
    Point a(32.3, 44);

    Point b(1.3, 3.5);

    CHECK_EQ(a.getX(), 32.3);

    CHECK_EQ(a.getY(), 44);

    CHECK_EQ(b.getX(), 1.3);

    CHECK_EQ(b.getY(), 3.5);
}

TEST_CASE("Point distance symmetry.")
{
    Point a(32.3, 44);

    Point b(1.3, 3.5);

    CHECK_EQ(a.distance(b), b.distance(a));
}

TEST_CASE("Point distance()")
{
    Point p1(0, 0);

    Point p2(3, 4);

    CHECK_EQ(p1.distance(p2), 5.0);

    CHECK_EQ(p2.distance(p1), 5.0);
}

// -----------------Character-------------------

TEST_CASE("Calculation of distance from Character to Character.")
{
    Point loc1(1, 2);

    Point loc2(1, 3);

    Cowboy *tom = new Cowboy("Tom", loc1);

    YoungNinja *sushi = new YoungNinja("sushi", loc2);

    double distance = tom->distance(sushi);

    CHECK_EQ(distance, loc1.distance(loc2));

    delete tom;

    delete sushi;
}

TEST_CASE("Character isAlive().")
{
    Point loc1(10, 20);

    Point loc2(11, 21);

    Cowboy *tom = new Cowboy("Tom", loc1);

    OldNinja *sushi = new OldNinja("sushi", loc2);

    CHECK_EQ(tom->getHitPoints(), 110);

    CHECK_EQ(sushi->getHitPoints(), 150);

    CHECK(tom->isAlive() == true);

    CHECK(sushi->isAlive() == true);

    sushi->slash(tom);

    CHECK(tom->isAlive() == true);

    CHECK(sushi->isAlive() == true);

    while (sushi->isAlive() && tom->hasBullets())
    {
        CHECK_NOTHROW(tom->shoot(sushi));
    }

    // Verify that tom throws an exception when shooting sushi without bullets
    CHECK_THROWS_AS(tom->shoot(sushi), std::runtime_error);

    // Check that either sushi is dead or tom has no bullets
    bool b1 = (sushi->isAlive() == false) || (tom->hasBullets() == false);

    CHECK(b1);

    // Reload tom's gun and continue shooting sushi until he dies
    while (sushi->isAlive())
    {
        tom->reload();
        CHECK_NOTHROW(tom->shoot(sushi));
    }

    // Verify that tom throws an exception when shooting sushi after he's already dead
    CHECK_THROWS_AS(tom->shoot(sushi), std::runtime_error);

    delete tom;

    delete sushi;
}

TEST_CASE("Character Hit Points")
{
    Point loc1(2, 3);

    Point loc2(3, 4);

    Cowboy *tom = new Cowboy("Tom", loc1);

    TrainedNinja *sushi = new TrainedNinja("sushi", loc2);

    CHECK(tom->getHitPoints() == 110);

    CHECK(sushi->getHitPoints() == 120);

    tom->hit(20);

    sushi->hit(30);

    CHECK(tom->getHitPoints() == 90);

    CHECK(sushi->getHitPoints() == 90);

    delete tom;

    delete sushi;
}

//------------Cowboy-------------------

TEST_CASE("Cowboy constructor.")
{
    Point loc(10, 20);

    Cowboy *tom = new Cowboy("Tom", loc);

    CHECK_EQ(tom->getName(), "Tom");

    CHECK_EQ(tom->getHitPoints(), 110);

    CHECK_EQ(tom->getLocation().getX(), 10);

    CHECK_EQ(tom->getLocation().getY(), 20);

    CHECK_EQ(tom->hasBullets(), true);

    delete tom;
}

TEST_CASE("Cowboy hasBullets().")
{
    Point loc(10, 20);

    Cowboy *tom = new Cowboy("Tom", loc);

    OldNinja *sushi = new OldNinja("sushi", loc);

    CHECK(tom->hasBullets() == true);

    tom->shoot(sushi);
    tom->shoot(sushi);
    tom->shoot(sushi);

    // Verify that the tom still has bullets
    CHECK(tom->hasBullets() == true);

    // Shoot 3 more bullets
    tom->shoot(sushi);
    tom->shoot(sushi);
    tom->shoot(sushi);

    // Verify that the tom no longer has bullets
    CHECK(tom->hasBullets() == false);

    delete tom;

    delete sushi;
}

TEST_CASE("Cowboy reload().")
{
    Point loc1(5, 3);

    Point loc2(8, 3);

    Cowboy *tom = new Cowboy("Tom", loc1);

    OldNinja *sushi = new OldNinja("sushi", loc2);

    CHECK(tom->hasBullets() == true);

    for (int i = 0; i < 6; i++)
    {
        tom->shoot(sushi);
    }

    CHECK(tom->hasBullets() == false);

    // Reload tom's gun
    tom->reload();

    CHECK(tom->hasBullets() == true);

    delete tom;

    delete sushi;
}

//------------OldNinja-------------------

TEST_CASE("OldNinja constructor.")
{
    Point loc(10, 20);

    OldNinja *sushi = new OldNinja("sushi", loc);

    CHECK_EQ(sushi->getName(), "sushi");

    CHECK_EQ(sushi->getHitPoints(), 150);

    CHECK_EQ(sushi->getLocation().getX(), 10);

    CHECK_EQ(sushi->getLocation().getY(), 20);

    CHECK_EQ(sushi->getSpeed(), 8);

    delete sushi;
}

//------------TrainedNinja-------------------

TEST_CASE("TrainedNinja constructor.")
{
    Point loc(10, 20);

    TrainedNinja *ninja = new TrainedNinja("ninja", loc);

    CHECK_EQ(ninja->getName(), "ninja");

    CHECK_EQ(ninja->getHitPoints(), 120);

    CHECK_EQ(ninja->getLocation().getX(), 10);

    CHECK_EQ(ninja->getLocation().getY(), 20);

    CHECK_EQ(ninja->getSpeed(), 12);

    delete ninja;
}

//------------YoungNinja-------------------

TEST_CASE("YoungNinja constructor.")
{
    Point loc(10, 20);

    YoungNinja *ninja = new YoungNinja("ninja", loc);

    CHECK_EQ(ninja->getName(), "ninja");

    CHECK_EQ(ninja->getHitPoints(), 100);

    CHECK_EQ(ninja->getLocation().getX(), 10);

    CHECK_EQ(ninja->getLocation().getY(), 20);

    CHECK_EQ(ninja->getSpeed(), 14);

    delete ninja;
}

//------------Cowboy shooting OldNinja-------------------

TEST_CASE("Cowboy shooting OldNinja")
{
    Point loc(10, 20);

    Cowboy *tom = new Cowboy("Tom", loc);

    OldNinja *sushi = new OldNinja("sushi", loc);

    CHECK(tom->getName() == "Tom");

    CHECK(tom->getHitPoints() == 110);

    CHECK(tom->hasBullets() == true);

    CHECK(sushi->getName() == "sushi");

    CHECK(sushi->getHitPoints() == 150);

    tom->shoot(sushi);

    CHECK(tom->hasBullets() == true);

    CHECK(sushi->getHitPoints() == 140);

    // Shoot when tom has no bullets
    tom->setBullets(0);

    REQUIRE_THROWS_AS(tom->shoot(sushi), std::runtime_error);

    delete tom;

    delete sushi;
}

//------------OldNinja moving towards Cowboy-------------------

TEST_CASE("OldNinja moving towards Cowboy.")
{
    Point loc1(10, 20);

    Point loc2(15, 25);

    Cowboy *tom = new Cowboy("Tom", loc1);

    OldNinja *sushi = new OldNinja("sushi", loc2);

    CHECK(tom->getName() == "Tom");

    CHECK(tom->getLocation().getX() == 10);

    CHECK(tom->getLocation().getY() == 20);

    CHECK(sushi->getName() == "sushi");

    CHECK(sushi->getLocation().getX() == 15);

    CHECK(sushi->getLocation().getY() == 25);

    sushi->move(tom);

    // Calculate the expected new location using moveTowards
    Point expectedLocation = Point::moveTowards(loc2, loc1, sushi->getSpeed());

    // Verify the new location
    INFO("Expected Location: (" << expectedLocation.getX() << ", " << expectedLocation.getY() << ")");

    INFO("Actual Location: (" << sushi->getLocation().getX() << ", " << sushi->getLocation().getY() << ")");

    CHECK(sushi->getLocation().getX() == expectedLocation.getX());

    CHECK(sushi->getLocation().getY() == expectedLocation.getY());

    delete tom;

    delete sushi;
}

TEST_CASE("OldNinja slashing Cowboy(1)- no damage to thr enemy.")
{
    Point loc1(10, 20);

    Point loc2(11, 21);

    Cowboy *tom = new Cowboy("Tom", loc1);

    OldNinja *sushi = new OldNinja("sushi", loc2);

    CHECK(tom->getName() == "Tom");

    CHECK(tom->getLocation().getX() == 10);

    CHECK(tom->getLocation().getY() == 20);

    CHECK(tom->getHitPoints() == 110);

    CHECK(sushi->getName() == "sushi");

    CHECK(sushi->getLocation().getX() == 11);

    CHECK(sushi->getLocation().getY() == 21);

    CHECK(sushi->getHitPoints() == 150);

    sushi->slash(tom);

    CHECK(tom->getHitPoints() == 110); // 110

    delete tom;

    delete sushi;
}

TEST_CASE("OldNinja slashing Cowboy(2) - the enemy is damaged.")
{
    Point loc1(10, 20);

    Point loc2(10, 21);

    Cowboy *tom = new Cowboy("Tom", loc1);

    OldNinja *sushi = new OldNinja("sushi", loc2);

    // Verify initial state
    CHECK(tom->getName() == "Tom");

    CHECK(tom->getLocation().getX() == 10);

    CHECK(tom->getLocation().getY() == 20);

    CHECK(tom->getHitPoints() == 110);

    CHECK(sushi->getName() == "sushi");

    CHECK(sushi->getLocation().getX() == 10);

    CHECK(sushi->getLocation().getY() == 21);

    sushi->slash(tom);

    CHECK(tom->getHitPoints() == 70); // 70

    delete tom;

    delete sushi;
}

TEST_CASE("Team with Leader and Character.")
{
    Point loc1(10, 20);

    Cowboy *tom = new Cowboy("Tom", loc1);

    Team team_A(tom);

    CHECK(team_A.getLeader()->getName() == "Tom");

    CHECK(team_A.getMembers().size() == 1);

    OldNinja *c4 = new OldNinja("OldNinja", Point(7, 8));

    team_A.add(c4);

    CHECK(team_A.getMembers().size() == 2);
}

TEST_CASE("Team with Maximum Characters.")
{

    Point loc1(1, 2);
    Point loc2(3, 4);
    Point loc3(5, 6);
    Point loc4(7, 8);
    Point loc5(9, 10);
    Point loc6(11, 12);
    Point loc7(13, 14);
    Point loc8(15, 16);
    Point loc9(16, 17);
    Point loc10(18, 19);

    Cowboy *Tom1 = new Cowboy("Tom1", loc1);
    Cowboy *Tom2 = new Cowboy("Tom2", loc2);
    Cowboy *Tom3 = new Cowboy("Tom3", loc3);
    Cowboy *Tom4 = new Cowboy("Tom4", loc4);
    Cowboy *Tom5 = new Cowboy("Tom5", loc5);

    OldNinja *sushi1 = new OldNinja("sushi1", loc6);
    TrainedNinja *sushi2 = new TrainedNinja("sushi2", loc7);
    YoungNinja *sushi3 = new YoungNinja("sushi3", loc8);
    YoungNinja *sushi4 = new YoungNinja("sushi4", loc9);
    YoungNinja *sushi5 = new YoungNinja("sushi5", loc10);

    Team team_A(Tom1);

    CHECK(team_A.getLeader()->getName() == "Tom1");

    CHECK(team_A.getMembers().size() == 1);

    team_A.add(Tom2);
    team_A.add(Tom3);
    team_A.add(Tom4);
    team_A.add(Tom5);
    team_A.add(sushi1);
    team_A.add(sushi2);
    team_A.add(sushi3);
    team_A.add(sushi4);
    team_A.add(sushi5);

    // Verify that the team now has the maximum number of characters (10)
    CHECK(team_A.getMembers().size() == 10);

    // Try to add one more character, which should throw an exception

    Cowboy *extraCharacter = new Cowboy("Extra Character", Point(100, 100));

    CHECK_THROWS_AS(team_A.add(extraCharacter), std::runtime_error);

    delete extraCharacter;
}

TEST_CASE("Team stillAlive().")
{

    Point loc1(10, 20);

    Cowboy *tom = new Cowboy("Tom", loc1);

    Team team_A(tom);

    CHECK(team_A.getLeader()->getName() == "Tom");

    CHECK(team_A.getMembers().size() == 1);

    // Add some members to the team
    YoungNinja *ninja1 = new YoungNinja("Ninja1", Point(7, 8));

    team_A.add(ninja1);

    OldNinja *ninja2 = new OldNinja("Ninja2", Point(5, 6));

    team_A.add(ninja2);

    // Check the number of alive members in the team
    CHECK(team_A.stillAlive() == 3);

    ninja1->hit(100);

    // Check the updated number of alive members in the team
    CHECK(team_A.stillAlive() == 2);
}

TEST_CASE("Team attack().")
{
    Point loc1(10, 20);

    Point loc2(30, 40);

    Cowboy *tom = new Cowboy("Tom", loc1);

    Cowboy *jerry = new Cowboy("Jerry", loc2);

    Team team_A(tom);

    Team team_B(jerry);

    // Add more members to the teams
    YoungNinja *sushi = new YoungNinja("Sushi", Point(7, 8));

    team_A.add(sushi);

    OldNinja *ramen = new OldNinja("Ramen", Point(5, 6));

    team_B.add(ramen);

    // Battle until one of the teams has no members left
    while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0)
    {
        CHECK_NOTHROW(team_A.attack(&team_B));
        CHECK_NOTHROW(team_B.attack(&team_A));
    }

    if (team_B.stillAlive() == 0)
    {
        CHECK_THROWS_AS(team_A.attack(&team_B), std::runtime_error);
    }

    if (team_A.stillAlive() == 0)
    {
        CHECK_THROWS_AS(team_B.attack(&team_A), std::runtime_error);
    }
}
