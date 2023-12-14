#include "Call.h"

// Implementation of the print function for the Call class
void Call::print() const
{
    std::cout << "Call Option\n";
    Option::print(); // Call the base class print method to avoid code duplication
}

// Implementation of the payoff function for the Call class
double Call::payoff(double spot) const
{
    // If the spot price is greater than the strike price, the payoff is (spot - strike)
    // Otherwise, the payoff is zero
    if (spot > strike) {
        return spot - strike;
    }
    else {
        return 0;
    }
}

// Implementation of the assignment operator for the Call class
Call& Call::operator=(const Call& c1)
{
    // Perform member-wise assignment
    if (this != &c1) {
        strike = c1.strike;
        maturity = c1.maturity;
    }
    return *this;
}