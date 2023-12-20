#include "Option.h"

// Default constructor for the Option class
Option::Option()
{
    // Initialize with default values
    strike = 100;
    maturity = 1;
    std::cout << "The Option object has been created" << std::endl;
}

// Parameterized constructor for the Option class
Option::Option(double strike, double maturity)
{
    // Initialize with provided values
    this->strike = strike;
    this->maturity = maturity;
    std::cout << "The Option object has been created" << std::endl;
    print();
}

// Copy constructor for the Option class
Option::Option(const Option& opt1)
{
    // Copy values from the source Option object
    this->strike = opt1.strike;
    this->maturity = opt1.maturity;
}

// Print function for the Option class
void Option::print() const
{
    std::cout << "Strike Price: " << strike << "\n";
    std::cout << "Maturity: " << maturity << " year(s)\n";
}

// Getter function for retrieving the strike price
double Option::get_strike() const
{
    return strike;
}

// Getter function for retrieving the maturity
double Option::get_maturity() const
{
    return maturity;
}

// Assignment operator for the Option class
Option& Option::operator=(const Option& opt1)
{
    if (this != &opt1) {
        // Perform member-wise assignment
        strike = opt1.strike;
        maturity = opt1.maturity;
    }
    return *this;
}
