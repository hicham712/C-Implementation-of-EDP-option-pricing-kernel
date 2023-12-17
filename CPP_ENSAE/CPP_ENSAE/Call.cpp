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

double Call::BS_price(double S, double K, double T, double r, double sigma) const
{
    double d1 = (log(S / K) + (r + 0.5 * pow(sigma, 2)) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    return S * (0.5+0.5*erf(d1 / sqrt(2))) - K * exp(-r * T) * (0.5 + 0.5 * erf(d2 / sqrt(2)));
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