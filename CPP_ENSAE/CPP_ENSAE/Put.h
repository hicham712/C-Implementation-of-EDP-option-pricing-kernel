#pragma once
#include "Option.h"
#include <iostream>
#include <algorithm>

// Class representing a put option, derived from the base class Option
class Put : public Option {
public:
    // Default constructor
    Put() : Option() {}

    // Parameterized constructor
    Put(double strike, double maturity) : Option(strike, maturity) {}

    // Copy constructor
    Put(const Put& c1) : Option(c1.strike, c1.maturity) {}

    // Destructor
    ~Put() override { std::cout << "Destructor for Put Option\n"; }

    // Override the print function to provide specific information about the put option
    void print() const override;

    // Override the payoff function to calculate the payoff for a put option
    double payoff(double spot) const override;

    // Override the assignment operator to perform member-wise assignment
    Put& operator=(const Put& c1);
};

