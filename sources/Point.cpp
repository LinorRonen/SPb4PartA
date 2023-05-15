#include "Point.hpp"
#include <cmath>
#include <string>

// Default constructor
Point::Point() : x(0), y(0) {}

// Constructor that get the value of x and y
Point::Point(double x, double y) : x(x), y(y) {}

// This function calculate the distance between this point and another point
double Point::distance(Point otherPoint) const 
{
    double dx = this->x - otherPoint.getX();
    double dy = this->y - otherPoint.getY();
    return std::sqrt(dx * dx + dy * dy);
}

// This function return a string that represent the point
std::string Point::print() const 
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

//moveTowards()
Point Point::moveTowards(const Point& curr, const Point& other, double distance) 
{
    double dx = other.x - curr.x;
    double dy = other.y - curr.y;
    double resultsqrt = std::sqrt(dx * dx + dy * dy);
    if (resultsqrt <= distance) 
    {
        return other;
    }
    double resultfornew = distance / resultsqrt;
    double newX = curr.x + dx * resultfornew;
    double newY = curr.y + dy * resultfornew;
    return Point(newX, newY);

}

// getX() function 
double Point::getX() const 
{
    return x;
}

// getY() function 
double Point::getY() const
{
    return y;
}


