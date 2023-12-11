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
	
	double get_rate() const;
	double get_vol() const;
	double get_spot() const;
	double get_div_yield() const;
	void summary();
	~Asset();
};

