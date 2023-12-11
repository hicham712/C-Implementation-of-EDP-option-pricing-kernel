#include "Asset.h"
#include <iostream>
using namespace std;

Asset::Asset()
{
	vol = 0.20;
	rate = 0.05;
	spot = 100;
	div_yield = 0;
	cout << "The Asset object has been created" << endl;
	summary();
}

Asset::Asset(double vol, double rate, double spot, double div_yield)
{
	this->vol = vol;
	this->rate = rate;
	this->spot = spot;
	this->div_yield = div_yield;
	cout << "The Asset object has been created" << endl;
	summary();
}

Asset::Asset(const Asset& myactif)
{
	this->vol = myactif.vol;
	this->rate = myactif.rate;
	this->spot = myactif.spot;
	this->div_yield = myactif.div_yield;
	cout << "The Asset object has been created by copy" << endl;
}

Asset::~Asset()
{
	cout << "The Asset object has been deleted" << endl;
}

double Asset::get_rate()
{

	return rate;
}

double Asset::get_vol()
{

	return vol;
}

double Asset::get_spot()
{
	return spot;
}

double Asset::get_div_yield()
{

	return div_yield;
}

void Asset::summary()
{
	cout << "My spot is: " << spot << endl;
	cout << "My volatility is: " << vol << endl;
	cout << "My rate is: " << rate << endl;
	cout << "My dividend yield is: " << div_yield << endl;
}


