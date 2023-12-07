
#include <iostream>
#include "Asset.h"
#include "Pricer.h"
int main()
{
    std::cout << "Hello World!\n";
    Asset myasset(0.01, 0.02, 0.01, 0.02);
<<<<<<< Updated upstream
    std::cout << "diiiiiiiiiiiv: "<< myasset.get_div_yield() << std::endl;
=======
    Pricer mypricer(myasset);
    std::cout << myasset.get_div_yield() << std::endl;
>>>>>>> Stashed changes
}

