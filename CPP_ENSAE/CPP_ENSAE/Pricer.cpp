#include "Pricer.h"
#include <iostream>
#include <cmath>
using namespace std;

Pricer::Pricer()
{
	this->Ntime = 100;
	this->Nspace = 100;
	this->Bounds = 2;
	cout << "The Pricer object has been created" << endl;
}

Pricer::Pricer(int Ntime, int Nspace, int Bounds)
{
	this->Ntime = Ntime;
	this->Nspace = Nspace;
	this->Bounds = Bounds;

	cout << "The Pricer object has been created" << endl;
}

Pricer::Pricer(const Pricer& mypricer)
{
	this->Ntime = mypricer.Ntime;
	this->Nspace = mypricer.Nspace;
	this->Bounds = mypricer.Bounds;
	cout << "The Pricer object has been created by copy" << endl;
}

void Pricer::create_vector(vector<double>& x, int start_in, int end_in, int num_in)
{

	double start = static_cast<double>(start_in);
	double end = static_cast<double>(end_in);
	double num = static_cast<double>(num_in);

	if (num == 1)
	{
		x.push_back(start);
	}
	double delta = (end - start) / (num - 1);

	for (int i = 0; i < num - 1; ++i)
	{
		x.push_back(start + delta * i);
	}
	x.push_back(end);
}
double Pricer::init_cond(const Option& opt,double cur_spot,double j) {
	return opt.payoff(cur_spot*exp(j));
}
void Pricer::set_initial_conditions(const Option& opt,const Asset& myAsset) {

	u_current.resize(Nspace+1, 0.0);
	u_previous.resize(Nspace+1, 0.0);
	create_vector(grid,-Bounds,Bounds,Nspace+1);
	for (int j = 0; j < Nspace+1; j=j+1) {
		u_previous[j] = init_cond(opt,myAsset.get_spot(),grid[j]);
	}
	
}
void Pricer::set_boundaries(double cur_spot, const Option& opt,int j,double time_to_mat) {
	u_current[0] =0.0;
	u_current[Nspace] = opt.payoff(cur_spot*exp(Bounds));
}
void Pricer::explicit_scheme(const Asset& myAsset,const Option& opt)
{
	double dt = opt.get_maturity() / Ntime;
	double dx = 2 * static_cast<double>(Bounds) / static_cast<double>(Nspace);
	double p = pow(myAsset.get_vol(), 2) * dt / 2 / pow(dx, 2) * (1 - dx / 2);
	double q = pow(myAsset.get_vol(), 2) * dt / 2 / pow(dx, 2) * (1 + dx / 2);
	set_initial_conditions(opt, myAsset);
	double time_to_mat = opt.get_maturity();

	for (int i = 0;i < Ntime;i++)
	{
		for (int j = Nspace - 1;j > 1;j--)
		{
			u_current[j] = p*u_previous[j+1]+q*u_previous[j-1]+(1-p-q)*u_previous[j];
			set_boundaries(myAsset.get_spot(),opt,j,time_to_mat);
		}
		u_previous = u_current;
		time_to_mat -= dt;
	}

}

Pricer::~Pricer()
{
	cout << "The Pricer object has been deleted" << endl;
}