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

double Put::BS_price(double S, double K, double T, double r, double sigma) const
{
    double d1 = (log(S / K) + (r + 0.5 * pow(sigma, 2)) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    return K * exp(-r * T) * (0.5+0.5*erf(-d2 / sqrt(2))) - S *(0.5+0.5* erf(-d1 / sqrt(2)));
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