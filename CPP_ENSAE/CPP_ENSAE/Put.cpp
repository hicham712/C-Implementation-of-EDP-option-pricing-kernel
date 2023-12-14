#include "Put.h"

// Implementation of the print function for the Put class
void Put::print() const
{
    std::cout << "Put Option\n";
    Option::print(); // Call the base class print method to avoid code duplication
}

// Implementation of the payoff function for the Put class
double Put::payoff(double spot) const
{
    // If the spot price is less than the strike price, the payoff is (strike - spot)
    // Otherwise, the payoff is zero
    if (spot < strike) {
        return strike - spot;
    }
    else {
        return 0;
    }
}

// Implementation of the assignment operator for the Put class
Put& Put::operator=(const Put& p1)
{
    // Perform member-wise assignment
    if (this != &p1) {
        strike = p1.strike;
        maturity = p1.maturity;
    }
    return *this;
}