#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <time.h>

#include "HLL.h"

/**
 * -f "input.txt" "output.txt"
 */
int main(int argc, char* argv[])
{
    if (argc != 4 || strcmp(argv[1], "-f") != 0)
    {
        std::cerr << "Write [key (-f)] [file.in] [file.out]" << std::endl;
        return 0;
    }
    if (!(freopen(argv[2], "r", stdin) && freopen(argv[3], "w", stdout)))
    {
        std::cerr << "Wrong filenames" << std::endl;
        return 0;
    }
    std::string a_str;
    std::getline(std::cin, a_str);
    std::stringstream stream_a(a_str);
    std::vector<int> a;
    int val;
    while (stream_a >> val)
    {
        a.push_back(val);
    }

    HLL counter(0.067);
    clock_t time = clock();
    counter.add_data(a);
    std::cout << counter.get_uniq_num() << std::endl;
    double time_spent = static_cast<double>(clock() - time) / CLOCKS_PER_SEC;
    std::cerr << "Success" << std::endl;
    std::cerr << "Time spent: " << std::setprecision(5) << time_spent << " seconds" << std::endl;
    return 0;
}