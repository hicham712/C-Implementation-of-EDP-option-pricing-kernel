#pragma once
#include "Asset.h"
class Pricer
{
	Asset Asset_choosen;
public:
	Pricer();
	Pricer(Asset);
	Pricer(const Pricer& mypricer);
	double Pay_offC(double Spot,double K);
	~Pricer();
	
};

