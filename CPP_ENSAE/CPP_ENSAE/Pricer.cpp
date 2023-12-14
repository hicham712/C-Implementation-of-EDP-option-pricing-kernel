#include "Pricer.h"
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Default constructor
Pricer::Pricer()
{
    this->Ntime = 100;
    this->Nspace = 100;
    this->Bounds = 2;
    cout << "The Pricer object has been created" << endl;
}

// Parameterized constructor
Pricer::Pricer(int Ntime, int Nspace, int Bounds)
{
    this->Ntime = Ntime;
    this->Nspace = Nspace;
    this->Bounds = Bounds;
    cout << "The Pricer object has been created" << endl;
}

// Copy constructor
Pricer::Pricer(const Pricer& mypricer)
{
    this->Ntime = mypricer.Ntime;
    this->Nspace = mypricer.Nspace;
    this->Bounds = mypricer.Bounds;
    cout << "The Pricer object has been created by copy" << endl;
}

// Function to create a vector with specified parameters
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

// Function to calculate the initial condition
double Pricer::init_cond(const Option& opt, double cur_spot, double j)
{
    return opt.payoff(cur_spot * exp(j));
}

// Function to calculate pu, pm, and pd based on the option method
void Pricer::calculate_Pu_Pm_Pd(const Option& opt, const Asset& myAsset, double& pu, double& pm, double& pd, bool explicit_method) const
{
    double dt = opt.get_maturity() / Ntime;
    double dx = 2 * static_cast<double>(Bounds) / static_cast<double>(Nspace);
    double sig2 = pow(myAsset.get_vol(), 2);
    double drift = myAsset.get_rate() - sig2 / 2;

    pu = dt * (0.5 * sig2 / pow(dx, 2) + drift * 0.5 / dx);
    pd = dt * (sig2 * 0.5 / pow(dx, 2) - drift * 0.5 / dx);
    if (explicit_method) {
        pm = 1 - dt * sig2 / pow(dx, 2) - myAsset.get_rate() * dt;
    }
    else {
        pm = 1 + pu + pd;
    }
}

// Function to create the A matrix for the implicit scheme
MatrixXd Pricer::implicit_create_A_matrix(double pu, double pm, double pd) const
{
    MatrixXd A_matrix = MatrixXd::Zero(Nspace - 1, Nspace - 1);

    for (int i = 0; i < Nspace - 2; i++) {
        A_matrix(i, i) = pm;
        A_matrix(i, i + 1) = -pu;
        A_matrix(i + 1, i) = -pd;
    }
    A_matrix(Nspace - 2, Nspace - 2) = pm;
    return A_matrix;
}

// Function to set the initial conditions for the explicit and implicit schemes
void Pricer::set_initial_conditions(const Option& opt, const Asset& myAsset)
{
    u_current.resize(Nspace + 1, 0.0);
    u_previous.resize(Nspace + 1, 0.0);
    create_vector(grid, -Bounds, Bounds, Nspace + 1);
    for (int j = 0; j < Nspace + 1; j++) {
        u_previous[j] = init_cond(opt, myAsset.get_spot(), grid[j]);
    }
}

// Function to set the boundary conditions at each time
void Pricer::set_boundaries(double cur_spot, const Option& opt, int j)
{
    u_current[0] = opt.payoff(cur_spot * exp(-Bounds));
    u_current[Nspace] = opt.payoff(cur_spot * exp(Bounds));
}

// Explicit scheme for option pricing
void Pricer::explicit_scheme(const Asset& myAsset, const Option& opt)
{
    double pu, pm, pd;
    calculate_Pu_Pm_Pd(opt, myAsset, pu, pm, pd, true);
    set_initial_conditions(opt, myAsset);

    for (int i = 0; i < Ntime; i++)
    {
        for (int j = Nspace - 1; j > 1; j--)
        {
            u_current[j] = pu * u_previous[j + 1] + pd * u_previous[j - 1] + pm * u_previous[j];
            set_boundaries(myAsset.get_spot(), opt, j);
        }
        u_previous = u_current;
    }
}

// Implicit scheme for option pricing
void Pricer::implicit_scheme(const Asset& myAsset, const Option& opt)
{
    // Calculate pu, pm, and pd based on the implicit method
    double pu, pm, pd;
    calculate_Pu_Pm_Pd(opt, myAsset, pu, pm, pd, false);

    // Create the A matrix and its inverse
    MatrixXd A_matrix = implicit_create_A_matrix(pu, pm, pd);
    MatrixXd u_inv_mat = A_matrix.inverse();

    // Initialize matrices for boundary conditions and results
    MatrixXd u_bounds = MatrixXd::Zero(Nspace - 1, 1);
    MatrixXd u_results = MatrixXd::Zero(Nspace + 1, Nspace + 1);
    double cur_spot = myAsset.get_spot();
    create_vector(grid, -Bounds, Bounds, Nspace + 1);

    // Set initial conditions at maturity
    for (int i = 0; i < Nspace + 1; i++) {
        u_results(i, Ntime) = init_cond(opt, myAsset.get_spot(), grid[i]);
    }

    // Perform backward iteration for implicit scheme
    for (int i = Ntime; i > 0; i--) {
        // Set boundary conditions
        u_bounds(0, 0) = -pd * opt.payoff(cur_spot * exp(-Bounds));
        u_bounds(Nspace - 2, 0) = -pu * opt.payoff(cur_spot * exp(Bounds));

        // Solve the implicit scheme equation
        u_results.block(1, i - 1, u_results.cols() - 2, 1) = u_inv_mat * (u_results.block(1, i, u_results.cols() - 2, 1) - u_bounds);

        // Set boundary conditions at each time step
        u_results(0, i - 1) = opt.payoff(cur_spot * exp(-Bounds));
        u_results(Nspace, i - 1) = opt.payoff(cur_spot * exp(Bounds));
    }

    // Output the results for the first row
    cout << "u_results ----------- row ----------------------" << endl;
    cout << u_results.col(0) << endl;
}

// Destructor
Pricer::~Pricer()
{
    cout << "The Pricer object has been deleted" << endl;
}
