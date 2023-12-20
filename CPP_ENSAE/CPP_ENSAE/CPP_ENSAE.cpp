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
    cout << "Execution time : " << duration(timeNow() - t1) / 1e6 << " msec" << endl;
}




void main_time_pricer_analysis()
{
    // Inputs
    int step = 100; // Variable que l'on peut modifier
    TimeVar tstart;
    TimeVar tstart2;

    // Input for pricer
    int Nspace = 100;
    int Ntime = 100;
    int Bounds = 2;
    int max_number = 15;
    vector<double> result_explicit;
    vector<double> result_implicit;
    // Create classes
    Asset myasset;
    Call callOption;

    vector<float> timeVectorExplicit;
    vector<float> timeVectorImplicit;

    for (int i = 2; i < (max_number* step) + 1; i += step) {

        // Creation des classes pricers
        Pricer myPricer(Ntime, Nspace, Bounds);

        //Function explicit
        tstart = timeNow();
        result_explicit = myPricer.explicit_scheme(myasset, callOption);
        timeVectorExplicit.push_back((duration(timeNow() - tstart) / 1e6));

        //Function implicit
        tstart2 = timeNow();
        result_implicit = myPricer.implicit_scheme(myasset, callOption);
        timeVectorImplicit.push_back((duration(timeNow() - tstart) / 1e6));

        Ntime += step;
    }
    cout << "-----> Vector of time for explicit_scheme" << endl;
    for (int i = 0; i < timeVectorExplicit.size(); i++) {
        cout << "Size " << (i + 1) * step << " = " << timeVectorExplicit[i] << " msec \n";
    }
    cout << endl;
    cout << "-----> Vector of time for implicit_scheme" << endl;
    for (int i = 0; i < timeVectorImplicit.size(); i++) {
        cout << "Size " << (i + 1) * step << " = " << timeVectorImplicit[i] << " msec \n";
    }
    cout << endl;
}
float average(std::vector<double> const& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
void fill_BS_prices(int Nspace,Option& myOpt,const Asset& myAsset,vector<double>& price_BS,vector<double>& spot_prices) {
    for (int i = 0;i < Nspace + 1;i++) {
        price_BS.push_back(myOpt.BS_price(myAsset.get_spot()*exp(spot_prices[i]), myAsset));
    }
}

void BS_VS_EDP(Asset& myAsset, Option& myOpt) {
    // Inputs
    const int NumScenarios = 3;
    int Nspaces[NumScenarios] = { 100, 100, 400 };
    int Ntimes[NumScenarios] = { 100, 1600, 1600 };
    int Bounds = 2;
    
    //create the pricers
    Pricer pricer1(Ntimes[0], Nspaces[0], 2);
    Pricer pricer2(Ntimes[1], Nspaces[1], 2);
    Pricer pricer3(Ntimes[2], Nspaces[2], 2);
    vector<Pricer> myPricers = { pricer1 , pricer2, pricer3 };
    // for outputs
    vector<vector<double>> result_explicits(NumScenarios);
    vector<vector<double>> result_implicits(NumScenarios);
    vector<vector<double>> spot_prices(NumScenarios);
    vector<vector<double>> prices_BS(NumScenarios);

    // Loop through different scenarios
    for (int i = 0; i < NumScenarios; ++i) {

        // Calculate explicit and implicit schemes
        result_explicits[i] = myPricers[i].explicit_scheme(myAsset, myOpt);
        result_implicits[i] = myPricers[i].implicit_scheme(myAsset, myOpt);

        // Create spot prices vector
        myPricers[i].create_vector(spot_prices[i], -Bounds, Bounds, Nspaces[i] + 1);

        // Fill Black-Scholes prices
        fill_BS_prices(Nspaces[i], myOpt, myAsset, prices_BS[i], spot_prices[i]);

        // Output average error for each scenario
        std::cout << "Average error for Nspace " << Nspaces[i] << " and Ntime " << Ntimes[i] << " is "
            << std::abs(average(prices_BS[i]) - average(result_explicits[i])) << std::endl;
    }
}


int main()
{
    // Inputs
    int Nspace = 400;
    int Ntime = 1600;
    int Bounds = 2;
    double vol = 0.2;
    double rates = 0.05;
    double maturity = 1;
    double spotPrice = 35;
    double strike = 30;

    // Fill classes
    Asset myasset(vol, rates, spotPrice);
    Call callOption(strike, maturity);

    // Pricing
    Pricer myPricer(Ntime, Nspace, Bounds);
    std::vector<double> result_explicit_ = myPricer.explicit_scheme(myasset, callOption);
    std::vector<double> result_implicit = myPricer.implicit_scheme(myasset, callOption);
    myPricer.get_price_explicit();
    cout << "Black and Scholes price: " << callOption.BS_price(myasset.get_spot(), myasset) << endl;

    // Comparaison with B&S method
    bool test_accuracy = true;
    if (test_accuracy) {
        cout << " -------- You have launched the comparaison between BS model and Explicit Scheme -------- " << endl;
        BS_VS_EDP(myasset, callOption);
    }

    // Time analysis
    bool test_speed = true;
    if (test_speed) {
        cout << " -------- You have launched the time analysis test --------" << endl;
        main_time_pricer_analysis();
    }
    return 0;

}

