#include <iostream>
#include "HLL.h"

int main()
{
    HLL hll(0.065);
    std::vector<int> test1 = {1, 1, 1, 1, 3, 1, 1, 1, 1, 2, 1, 1, 8, 7, 5, 4, 1, 6};
    for (auto e : test1)
    {
        hll.add(e);
    }
    std::cout << hll.get_uniq_num();
    return 0;
}
