#pragma once
#include <iostream>
class Option
{
protected:
	double strike;
	double maturity;
public:
	Option();
	Option(double strike, double maturity);
	Option(const Option& opt1);
	virtual ~Option() {}
	virtual void print() const;
	virtual double payoff(double spot) const = 0;

	double get_strike() const;
	double get_maturity() const;
	Option& operator=(const Option& opt1);
};

