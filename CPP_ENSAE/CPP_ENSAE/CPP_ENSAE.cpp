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
    vector<float> timeVectorExplicit;
    vector<float> timeVectorImplicit;
    int step = 100; // Variable que l'on peut modifier
    TimeVar tstart;
    TimeVar tstart2;

    int Nspace = 100;
    int Ntime = 100;
    int Bounds = 2;
    vector<double> result_explicit;
    vector<double> result_implicit;

    for (int i = 2; i < 1000; i += step) {

        Asset myasset(0.20, 0.02, 100, 0.02);
        Call callOption(100.0, 1.0);
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
void fill_BS_prices(int Nspace,Option& myOpt,Asset myAsset,vector<double>& price_BS,vector<double>& spot_prices) {
    for (int i = 0;i < Nspace + 1;i++) {
        price_BS.push_back(myOpt.BS_price(myAsset.get_spot()*exp(spot_prices[i]),myOpt.get_strike(),myOpt.get_maturity(),myAsset.get_rate(),myAsset.get_vol()));
    }
}

void BS_VS_EDP(Asset myAsset,Option& myOpt) {
    int Nspaces[3] = { 100, 100,400 };;
    int Ntimes[3] = { 100,400,1000 };
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
    cout << "average error for Nspace 100 and Ntime 100 is " << abs((average(price1_BS)-average(result_explicit1_))/myAsset.get_spot()) << "% "<< endl;
    cout << "average error for Nspace 100 and Ntime 100 is " << abs((average(price2_BS) - average(result_explicit2_)) / myAsset.get_spot()) << "% " << endl;
    cout << "average error for Nspace 100 and Ntime 100 is " << abs((average(price3_BS) - average(result_explicit3_)) / myAsset.get_spot()) << "% " << endl;
}


int main()
{
    // Inputs
    int Nspace = 100;
    int Ntime = 100;
    int Bounds = 2;
    double vol = 0.2;
    double rates = 0.05;
    double maturity = 1;
    double spotPrice = 200;
    double strike = 100;
    double div_yield = 0;

    // Fill classes
    Asset myasset(vol, rates, spotPrice, div_yield);
    Call callOption(strike, maturity);

    // Pricing
    Pricer myPricer(Ntime, Nspace, Bounds);
    std::vector<double> result_explicit_ = myPricer.explicit_scheme(myasset, callOption);
    std::vector<double> result_implicit = myPricer.implicit_scheme(myasset, callOption);

    // Comparaison with B&S method
    bool test_accuracy = true;
    if (test_accuracy) {
        BS_VS_EDP(myasset, callOption);
    }

    // Time analysis
    bool test_speed = false;
    if (test_speed) {
        main_time_pricer_analysis();
    }
    return 0;

}

