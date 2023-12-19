#pragma once
#include "Option.h"
#include <iostream>
#include <algorithm>

// Class representing a call option, derived from the base class Option
class Call : public Option {
public:
    // Default constructor
    Call() : Option() {}

    // Parameterized constructor
    Call(double strike, double maturity) : Option(strike, maturity) {}

    // Copy constructor
    Call(const Call& c1) : Option(c1.strike, c1.maturity) {}

    // Destructor
    ~Call() override { std::cout << "Destructor for Call Option\n"; }

    // Override the print function to provide specific information about the call option
    void print() const override;

    // Override the payoff function to calculate the payoff for a call option
    double payoff(double spot) const override;

    // Override the BS function to calculate the option price according to Black & Scholes 
    double BS_price(const double spot, const Asset& myAsset) const override;

    // Override the assignment operator to perform member-wise assignment
    Call& operator=(const Call& c1);
};

