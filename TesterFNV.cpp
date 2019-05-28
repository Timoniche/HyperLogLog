#include "FNV.h"
#include <iostream>
#include <bitset>

int main()
{
    int input[10] = {1, 2, 3, 4, 5,
                     6, 7, 8, 9, 10};
    std::cout << std::bitset<32>(FNV::count_data(input)) << std::endl;
    return 0;
}

