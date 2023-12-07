
#include <iostream>
#include "Asset.h"
int main()
{
    std::cout << "Hello World!\n";
    Asset myasset(0.01, 0.02, 0.01, 0.02);
    std::cout << "diiiiiiiiiiiv: "<< myasset.get_div_yield() << std::endl;
}

