#include "Pricer.h"
#include <iostream>
using namespace std;

Pricer::Pricer()
{
	cout << "The Pricer object has been created" << endl;
}

Pricer::Pricer(Asset Asset_choosen)
{
	this->Asset_choosen = Asset_choosen;

	cout << "The Pricer object has been created" << endl;
}

Pricer::Pricer(const Pricer& mypricer)
{
	this->Asset_choosen = mypricer.Asset_choosen;
	cout << "The Pricer object has been created by copy" << endl;
}


double Pricer::Pay_offC(double Spot,double K)
{
	return (Spot - K) * (Spot > K);
}

Pricer::~Pricer()
{
	cout << "The Pricer object has been deleted" << endl;
}