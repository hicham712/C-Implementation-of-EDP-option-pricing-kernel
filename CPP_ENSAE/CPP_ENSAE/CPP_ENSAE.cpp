
#include <iostream>
#include "Asset.h"
#include "Option.h"
#include "Call.h"
using namespace std;
int main()
{
    std::cout << "Hello World!\n";
    Asset myasset(0.01, 0.02, 0.01, 0.02);
    std::cout << "diiiiiiiiiiiv: "<< myasset.get_div_yield() << std::endl;

    Call callOption(100.0, 1.5);
    cout << " --- print all info" << endl;
    callOption.print();

    double spotPrice = 105.0; 
    std::cout << "Call Option Payoff: " << callOption.payoff(spotPrice) << "\n";

    cout << "----------------------- Test override = ---------------------------" << endl;
    Call c2;
    c2.print();
    c2 = callOption;
    cout << " New c2 = ---------------------------" << endl;
    c2.print();


    return 0;

}

