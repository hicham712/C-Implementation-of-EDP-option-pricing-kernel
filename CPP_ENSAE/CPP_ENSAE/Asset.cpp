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
}

Asset::Asset(double vol, double rate, double spot, double div_yield)
{
	this->vol = vol;
	this->rate = rate;
	this->spot = spot;
	this->div_yield = div_yield;
	cout << "The Asset object has been created" << endl;
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
	cout<< "Myrate is: " <<rate<< endl;
	return rate;
}

double Asset::get_vol()
{
	cout << "Myrate is: " << vol << endl;
	return vol;
}

double Asset::get_spot()
{
	cout << "Myrate is: " << spot << endl;
	return spot;
}

double Asset::get_div_yield()
{
	cout << "Myrate is: " << div_yield << endl;
	return div_yield;
}
