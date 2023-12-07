// CPP_ENSAE.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Asset.h"
int main()
{
    std::cout << "Hello World!\n";
    Asset myasset(0.01, 0.02, 0.01, 0.02);
    std::cout << myasset.get_div_yield() << std::endl;
}

