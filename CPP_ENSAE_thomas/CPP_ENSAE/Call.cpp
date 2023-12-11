#include "Call.h"

void Call::print() const
{
	std::cout << "Call Option\n";
	Option::print(); // Call the base class print method to avoid code duplication
}

double Call::payoff(double spot) const
{
	if (spot > strike) {
		return spot - strike;
	}
	else {
		return 0;
	}

}

Call& Call::operator=(const Call& c1)
{
	strike = c1.strike;
	maturity = c1.maturity;
	return *this;
}


