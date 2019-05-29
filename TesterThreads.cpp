#include <set>
//#include <random>
#include <cassert>
#include <vector>

#include "HLL.h"

double relative_error(int expected, int got) {
    return abs(got - expected) / (double) expected;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    const int N = (int) 1e6;
    std::vector<int> data;
    for (int k : {1, 10, 1000, 10000, N / 10, N, N * 10}) {
        data.clear();
        std::uniform_int_distribution<> dis(1, k);
        std::set<int> all;
        HLL counter(0.067);
        for (int i = 0; i < N; i++) {
            int value = dis(gen);
            all.insert(value);
            //counter.add(value);
            data.push_back(value);
        }
        counter.add_data(data);
        int expected = (int) all.size();
        int counter_result = counter.get_uniq_num();
        double error = relative_error(expected, counter_result);
        printf("%d numbers in range [1 .. %d], %d uniq, %d result, %.5f relative error\n", N, k, expected, counter_result, error);
        assert(error <= 0.1);
    }
    HLL counter(0.067);
    printf("%.5f size in kb\n", double(sizeof(counter)) / 1024);

    return 0;
}

