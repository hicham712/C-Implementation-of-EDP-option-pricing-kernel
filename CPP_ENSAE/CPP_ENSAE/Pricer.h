#pragma once
#include "Asset.h"
#include "Option.h"
#include <vector>
#include <Eigen/Dense>  // Include Eigen for MatrixXd
using namespace std;

// Class representing a financial pricer for option valuation
class Pricer {
    int Ntime;                  // Number of time steps
    int Nspace;                 // Number of space steps
    int Bounds;                 // Bounds for the option pricing grid
    vector<double> u_current;   // Vector representing the current solution
    vector<double> u_previous;  // Vector representing the previous solution
    vector<double> grid;        // Vector representing the spatial grid


    // Private member functions for setting initial conditions and handling boundaries
    void set_initial_conditions(const Option& opt, const Asset& myAsset);
    double init_cond(const Option& opt, double cur_spot, double j);

    // Private member function to calculate pu, pm, and pd based on the option method
    void calculate_Pu_Pm_Pd(const Option& opt, const Asset& myAsset, double& pu, double& pm, double& pd, bool explicit_method) const;

    // Private member function to create the A matrix for the implicit scheme
    Eigen::MatrixXd implicit_create_A_matrix(double pu, double pm, double pd) const;

public:
    // Default constructor
    Pricer();

    // Parameterized constructor
    Pricer(int Ntime, int Nspace, int Bounds);

    // Copy constructor
    Pricer(const Pricer& mypricer);

    // Function to create a vector with specified parameters
    void create_vector(vector<double>& x, int start_in, int end_in, int num_in);

    // Explicit scheme for option pricing
    vector<double> explicit_scheme(const Asset& myAsset, const Option& opt);

    // Implicit scheme for option pricing
    vector<double> implicit_scheme(const Asset& myAsset, const Option& opt);

    // Function to set boundaries for the option pricing grid
    void set_boundaries(double cur_spot, const Option& opt);

    // Destructor
    ~Pricer();
};