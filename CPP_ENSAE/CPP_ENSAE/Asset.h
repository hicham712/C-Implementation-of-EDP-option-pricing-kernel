#pragma once

// Class representing financial asset details
class Asset
{
    double vol;        // Volatility of the asset
    double rate;       // Risk free rate
    double spot;       // Current spot price of the asset

public:
    // Default constructor
    Asset();

    // Parameterized constructor
    Asset(double vol, double rate, double spot);

    // Copy constructor
    Asset(const Asset& myactif);

    // Getter function for retrieving the interest rate
    double get_rate() const;

    // Getter function for retrieving the volatility
    double get_vol() const;

    // Getter function for retrieving the spot price
    double get_spot() const;

    // Display a summary of the asset details
    void summary();

    // Override the assignment operator to perform member-wise assignment
    Asset& operator=(const Asset& asset1);

    // Destructor
    ~Asset();
};
