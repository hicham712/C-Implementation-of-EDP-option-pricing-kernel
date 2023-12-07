#pragma once
class Asset
{
	double vol;
	double rate;
	double spot;
	double div_yield;
public:
	Asset();
	Asset(double vol, double rate, double spot, double div_yield);
	Asset(const Asset& myactif);
	~Asset();

	
	double get_rate();
	double get_vol();
	double get_spot();
	double get_div_yield();

};

