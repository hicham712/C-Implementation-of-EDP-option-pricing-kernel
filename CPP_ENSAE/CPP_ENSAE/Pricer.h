#pragma once
#include "Asset.h"
#include "Option.h"
#include <vector>
using namespace std;
class Pricer
{
	int Ntime;
	int Nspace;
    int Bounds;
    vector<double> u_current;
    vector<double> u_previous;
    vector<double> grid;
    void set_initial_conditions(const Option& opt, const Asset& myAsset);
    double init_cond(const Option& opt, double cur_spot, double j);
public:
	Pricer();
	Pricer(int Ntime,int Nspace,int Bounds);
    Pricer(const Pricer& mypricer);
    void create_vector(vector<double>& x, int start_in, int end_in, int num_in);
    void explicit_scheme(const Asset& myAsset,const Option& opt);
    void set_boundaries(double cur_spot, const Option& opt,int j,double time_to_mat);
	~Pricer();
	
};



