#include "Asset.h"
#include <iostream>
using namespace std;

// Default constructor for the Asset class
Asset::Asset()
{
    // Initialize with default values
    vol = 0.20;
    rate = 0.05;
    spot = 100;

    cout << "The Asset object has been created" << endl;
    summary(); // Display a summary of the asset details
}

// Parameterized constructor for the Asset class
Asset::Asset(double vol, double rate, double spot)
{
    // Initialize with provided values
    this->vol = vol;
    this->rate = rate;
    this->spot = spot;

    cout << "The Asset object has been created" << endl;
    summary(); // Display a summary of the asset details
}

// Copy constructor for the Asset class
Asset::Asset(const Asset& myactif)
{
    // Copy values from the source Asset object
    this->vol = myactif.vol;
    this->rate = myactif.rate;
    this->spot = myactif.spot;

    cout << "The Asset object has been created by copy" << endl;
}

Asset& Asset::operator=(const Asset& asset1)
{
    if (this!= &asset1) {
        // Use the copy constructor to perform member-wise copy
        *this = Asset(asset1);
    }

    // Return a reference to the modified object
    return *this;
}

// Destructor for the Asset class
Asset::~Asset()
{
    cout << "The Asset object has been deleted" << endl;
}

// Getter function for retrieving the interest rate
double Asset::get_rate() const
{
    return rate;
}

// Getter function for retrieving the volatility
double Asset::get_vol() const
{
    return vol;
}

// Getter function for retrieving the spot price
double Asset::get_spot() const
{
    return spot;
}

// Display a summary of the asset details
void Asset::summary()
{
    cout << "My spot is: " << spot << endl;
    cout << "My volatility is: " << vol << endl;
    cout << "My rate is: " << rate << endl;


}
