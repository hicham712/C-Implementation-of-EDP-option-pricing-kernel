#include "Pricer.h"
#include <iostream>
#include <cmath>
#include <eigen/Eigen>

using namespace std;
using namespace Eigen;
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
	for (int j = 0; j < Nspace+1; j++) {
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
	double sig2 = pow(myAsset.get_vol(), 2);
	double drift = myAsset.get_rate() - sig2 / 2;
	double pu = dt * (0.5 * sig2 / pow(dx, 2) + drift * 0.5 / dx);
	double pm = 1 - dt * sig2 / pow(dx, 2) - myAsset.get_rate() * dt;
	double pd = dt * (sig2 * 0.5 / pow(dx, 2) - drift*0.5/dx);
	set_initial_conditions(opt, myAsset);
	double time_to_mat = opt.get_maturity();

	for (int i = 0;i < Ntime;i++)
	{
		for (int j = Nspace - 1;j > 1;j--)
		{
			u_current[j] = pu* u_previous[j + 1] + pd * u_previous[j - 1] + pm* u_previous[j];
			set_boundaries(myAsset.get_spot(),opt,j,time_to_mat);
		}
		u_previous = u_current;
		time_to_mat -= dt;
	}

}

void Pricer::implicit_scheme(const Asset& myAsset, const Option& opt)
{
	double dt = opt.get_maturity() / Ntime;
	double dx = 2 * static_cast<double>(Bounds) / static_cast<double>(Nspace);
	double sig2 = pow(myAsset.get_vol(), 2);
	double drift = myAsset.get_rate() - sig2 / 2;
	double pu = dt * (0.5 * sig2 / pow(dx, 2) + drift * 0.5 / dx);
	double pd = dt * (sig2 * 0.5 / pow(dx, 2) - drift * 0.5 / dx);
	double pm = 1 +pu+pd;
	double time_to_mat = opt.get_maturity();


	MatrixXd A_matrix = MatrixXd::Zero(Nspace - 1, Nspace - 1);
	for (int i = 0;i < Nspace - 2;i++) {
		A_matrix(i, i) = pm ; //
		A_matrix(i, i + 1) = -pu ; 
		A_matrix(i + 1, i) = -pd; 
	}
	A_matrix(Nspace - 2, Nspace - 2) = pm;
	
	MatrixXd u_inv_mat = A_matrix.inverse();
	cout << "INVVVVVV----------- INV----------------------" << endl;
	cout << A_matrix << endl;
	MatrixXd u_bounds = MatrixXd::Zero(Nspace - 1, 1);
	MatrixXd u_results= MatrixXd::Zero(Nspace + 1, Nspace + 1);
	double cur_spot = myAsset.get_spot();
	create_vector(grid, -Bounds, Bounds, Nspace + 1);

	for (int i = 0;i < Nspace+1;i++) {
		u_results(i, Ntime) = init_cond(opt, myAsset.get_spot(), grid[i]); 
	}
	
	for (int i = Ntime;i > 0;i--) {
		u_bounds(0, 0) = -pd * opt.payoff(cur_spot * exp(-Bounds));
		u_bounds(Nspace - 2, 0) = -pu * opt.payoff(cur_spot * exp(Bounds));


		u_results.block(1,i-1, u_results.cols() - 2, 1)= u_inv_mat * (u_results.block(1, i, u_results.cols() - 2, 1) -u_bounds);
		
		u_results(0, i-1) = opt.payoff(cur_spot * exp(-Bounds));
		u_results(Nspace, i - 1 ) = opt.payoff(cur_spot * exp(Bounds));

		
	}

	cout << "u_results----------- row----------------------" << endl;
	cout << u_results.col(0) << endl;
}

Pricer::~Pricer()
{
	cout << "The Pricer object has been deleted" << endl;
}