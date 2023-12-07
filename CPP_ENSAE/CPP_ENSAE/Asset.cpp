#include "Asset.h"
using namespace std;

Asset::Asset()
{
	vol = 0.20;
	rate = 0.05;
	spot = 100;
	div_yield = 0;
}

Asset::Asset(double vol, double rate, double spot, double div_yield)
{
	this->vol = vol;
	this->rate = rate;
	this->spot = spot;
	this->div_yield = div_yield;
}

Asset::Asset(const Asset& myactif)
{
	this->vol = myactif.vol;
	this->rate = myactif.rate;
	this->spot = myactif.spot;
	this->div_yield = myactif.div_yield;
}

Asset::~Asset()
{
}

double Asset::get_rate()
{
	std::cout<< "Myrate is: " <<rate<< endl;
}

double Asset::get_vol()
{
	return 0.0;
}

double Asset::get_spot()
{
	return 0.0;
}

double Asset::get_div_yield()
{
	return 0.0;
}
