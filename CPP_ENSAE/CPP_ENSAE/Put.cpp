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

double Put::BS_price(const double spot, const Asset& myAsset) const
{
    double d1 = (log(spot / strike) + (myAsset.get_rate() + 0.5 * pow(myAsset.get_vol(), 2)) * maturity) / (myAsset.get_vol() * sqrt(maturity));
    double d2 = d1 - myAsset.get_vol() * sqrt(maturity);
    return strike * exp(-myAsset.get_rate() * maturity) * (0.5 + 0.5 * erf(-d2 / sqrt(2))) - spot * (0.5 + 0.5 * erf(-d1 / sqrt(2)));
};


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