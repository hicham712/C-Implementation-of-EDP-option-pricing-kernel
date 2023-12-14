
#include <iostream>
#include "Asset.h"
#include "Option.h"
#include "Call.h"
#include "Put.h"
#include "Pricer.h"
#include <chrono>
#include <vector>

using namespace std;

// Installation de chrono
typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) \
  std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()
// Fonction permettant de calculer le temps d'execution entre t1 et maintenant
void printTime(TimeVar t1) {
    cout << "Execution time : " << duration(timeNow() - t1) / 1e9 << " sec" << endl;
}


void main_time_pricer_analysis()
{
    vector<float> timeVectorSpace;
    vector<float> timeVectorTime;
    int step = 1000; // Variable que l'on peut modifier
    TimeVar tstart;
    TimeVar tstart2;

    int Nspace = 1000;
    int Ntime = 1000;
    int Bounds = 2;
    for (int i = 2; i < 10001; i += step) {

        Asset myasset(0.20, 0.02, 100, 0.02);
        Call callOption(100.0, 1.0);
        // Creation des classes pricers
        Pricer myPricer1(Ntime, Nspace, Bounds);
        myPricer1.explicit_scheme(myasset, callOption);

        //Function
        timeVectorSpace.push_back((duration(timeNow() - tstart) / 1e6));

        tstart2 = timeNow();
        Pricer myPricer2(Ntime, Nspace, Bounds);
        myPricer2.explicit_scheme(myasset, callOption);
        timeVectorTime.push_back((duration(timeNow() - tstart2) / 1e6));

        Nspace += step;
        Ntime += step;
    }
    cout << "-----> Vector of time for space variation" << endl;
    for (int i = 0; i < timeVectorSpace.size(); i++) {
        cout << "Size " << (i + 1) * step << " = " << timeVectorSpace[i] << "msec \n";
    }
    cout << endl;
    cout << "-----> Vector of time for time variation" << endl;
    for (int i = 0; i < timeVectorTime.size(); i++) {
        cout << "Size " << (i + 1) * step << " = " << timeVectorTime[i] << "msec \n";
    }
    cout << endl;
}

int main()
{
    int Nspace = 20;
    int Ntime = 20;
    int Bounds = 2;
    double vol = 0.2;
    double rates = 0.0;
    double maturity = 1;
    double spotPrice = 105;
    double strike = 100;
    double div_yield = 0;

    Asset myasset(vol, rates, spotPrice, div_yield); // 	Asset(double vol, double rate, double spot, double div_yield);
    Put callOption(strike, maturity); // Option(strike, maturity) 
    cout << " --- print all info" << endl;
    callOption.print();

    std::cout << "Call Option Payoff: " << callOption.payoff(spotPrice) << "\n";

    cout << "----------------------- Pricing = ---------------------------" << endl;
    Put c2;
    Pricer myPricer(Ntime, Nspace,2);
    myPricer.explicit_scheme(myasset, callOption);
    myPricer.implicit_scheme(myasset, callOption);

    // time analasis
    bool test = false;
    if (test) {
        main_time_pricer_analysis();
    }
    return 0;

}

