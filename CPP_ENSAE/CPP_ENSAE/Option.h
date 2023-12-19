#pragma once
#pragma once
#include <iostream>
#include "Asset.h"
// Base class representing a financial option
class Option {
protected:
    // Data members for strike price and maturity
    double strike;
    double maturity;

public:
    // Default constructor
    Option();

    // Parameterized constructor
    Option(double strike, double maturity);

    // Copy constructor
    Option(const Option& opt1);

    // Virtual destructor to allow proper cleanup in derived classes
    virtual ~Option() {}

    // Virtual function to print option details
    virtual void print() const;

    // Virtual function to get the BS price of the option
    virtual double BS_price(const double spot, const Asset& myAsset) const = 0;

    // Pure virtual function to calculate the payoff, making Option an abstract class
    virtual double payoff(double spot) const = 0;

    // Getter function for retrieving the strike price
    double get_strike() const;

    // Getter function for retrieving the maturity
    double get_maturity() const;

    // Assignment operator for the Option class
    Option& operator=(const Option& opt1);
};