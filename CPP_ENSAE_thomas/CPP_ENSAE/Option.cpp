#include "Option.h"

Option::Option()
{
    strike = 100;
    maturity = 1;
    std::cout << "The Option object has been created" << std::endl;
}

Option::Option(double strike, double maturity)
{
    this->strike = strike;
    this->maturity = maturity;
    std::cout << "The Option object has been created" << std::endl;
}

Option::Option(const Option& opt1)
{
    this->strike = opt1.strike;
    this->maturity = opt1.maturity;
}


void Option::print() const
{
    std::cout << "Strike Price: " << strike << "\n";
    std::cout << "Maturity: " << maturity << " year(s)\n";
}


double Option::get_strike() const
{
    return strike;
}

double Option::get_maturity() const
{
    return maturity;
}

Option& Option::operator=(const Option& opt1)
{
    strike = opt1.strike;
    maturity = opt1.maturity;
    return *this;
}
