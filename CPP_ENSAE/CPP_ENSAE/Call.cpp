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

double Call::BS_price(const double spot, const Asset& myAsset) const
{
    double d1 = (log(spot / strike) + (myAsset.get_rate() + 0.5 * pow(myAsset.get_vol(), 2)) * maturity) / (myAsset.get_vol() * sqrt(maturity));
    double d2 = d1 - myAsset.get_rate() * sqrt(maturity);
    return spot * (0.5 + 0.5 * erf(d1 / sqrt(2))) - strike * exp(-myAsset.get_rate() * maturity) * (0.5 + 0.5 * erf(d2 / sqrt(2)));
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