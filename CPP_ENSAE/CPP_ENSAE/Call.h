#pragma once
#include "Option.h"
#include <iostream>
#include <algorithm> 
class Call : public Option
{

public:
	Call() : Option(){}
	Call(double strike, double maturity) : Option(strike, maturity) {}
	Call(const Call& c1) : Option(c1.strike, c1.maturity) {}

	~Call()  override{ std::cout << "Destructor for Call Option\n"; }

	void print() const override;
	double payoff(double spot) const override;
	Call& operator=(const Call& c1);

};

