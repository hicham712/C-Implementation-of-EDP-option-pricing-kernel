
#include <iostream>
#include "Asset.h"
#include "Option.h"
#include "Call.h"
#include "Put.h"
#include "Pricer.h"
#include <chrono>
#include <vector>
#include <numeric>
#include <Eigen/Dense>


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
float average(std::vector<double> const& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
void fill_BS_prices(int Nspace,Option& myOpt,Asset myAsset,vector<double>& price_BS,vector<double>& spot_prices) {
    for (int i = 0;i < Nspace + 1;i++) {
        price_BS.push_back(myOpt.BS_price(myAsset.get_spot()*exp(spot_prices[i]),myOpt.get_strike(),myOpt.get_maturity(),myAsset.get_rate(),myAsset.get_vol()));
    }
}

void BS_VS_EDP(Asset myAsset,Option& myOpt) {
    int Nspaces[3] = { 100, 400,1000 };;
    int Ntimes[3] = { 100,250,250 };
    int Bounds = 2;
    
    Pricer myPricer1(Ntimes[0], Nspaces[0], 2);
    std::vector<double> result_explicit1_=myPricer1.explicit_scheme(myAsset, myOpt);
    std::vector<double> result_implicit1_ = myPricer1.implicit_scheme(myAsset, myOpt);
    Pricer myPricer2(Ntimes[1], Nspaces[1], 2);
    std::vector<double> result_explicit2_ = myPricer2.explicit_scheme(myAsset, myOpt);
    std::vector<double> result_implicit2_ = myPricer2.implicit_scheme(myAsset, myOpt);
    Pricer myPricer3(Ntimes[2], Nspaces[2], 2);
    std::vector<double> result_explicit3_ = myPricer3.explicit_scheme(myAsset, myOpt);
    std::vector<double> result_implicit3_ = myPricer3.implicit_scheme(myAsset, myOpt);

    vector <double> spot_prices1,spot_prices2,spot_prices3;
    myPricer1.create_vector(spot_prices1, -Bounds, Bounds, Nspaces[0] + 1);
    myPricer2.create_vector(spot_prices2, -Bounds, Bounds, Nspaces[1] + 1);
    myPricer2.create_vector(spot_prices3, -Bounds, Bounds, Nspaces[2] + 1);
    vector <double> price1_BS, price2_BS, price3_BS;
    fill_BS_prices(Nspaces[0], myOpt,myAsset,price1_BS, spot_prices1);
    fill_BS_prices(Nspaces[1], myOpt, myAsset, price2_BS, spot_prices2);
    fill_BS_prices(Nspaces[2], myOpt, myAsset, price3_BS, spot_prices3);
    cout << "average error for Nspace 100 and Ntime 100 is " << abs(average(price1_BS)-average(result_implicit1_)) << endl;
    cout << "average error for Nspace 100 and Ntime 100 is " << abs(average(price2_BS) - average(result_implicit2_)) << endl;
    cout << "average error for Nspace 100 and Ntime 100 is " << abs(average(price3_BS) - average(result_implicit3_)) << endl;
}


int main()
{
    int Nspace = 20;
    int Ntime = 20;
    int Bounds = 2;
    double vol = 0.2;
    double rates = 0.05;
    double maturity = 1;
    double spotPrice = 105;
    double strike = 100;
    double div_yield = 0;

    Asset myasset(vol, rates, spotPrice, div_yield); // 	Asset(double vol, double rate, double spot, double div_yield);
    Call callOption(strike, maturity); // Option(strike, maturity) 
    cout << " --- print all info" << endl;
    callOption.print();

    std::cout << "Call Option Payoff: " << callOption.payoff(spotPrice) << "\n";

    cout << "----------------------- Pricing = ---------------------------" << endl;
    Call c2;
    Pricer myPricer(Ntime, Nspace,2);
    std::vector<double> result_explicit_=myPricer.explicit_scheme(myasset, callOption);
    std::vector<double> result_implicit= myPricer.implicit_scheme(myasset, callOption);

    // time analasis
    bool test = true;
    if (test) {
        //main_time_pricer_analysis();
        BS_VS_EDP(myasset, callOption);
    }
    return 0;

}

