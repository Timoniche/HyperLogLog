#ifndef HYPERLOGLOG_HLL_H
#define HYPERLOGLOG_HLL_H

#include <cstddef>
#include <random>
#include <limits>
#include <vector>
#include <thread>

#include "FNV.h"

/**
 * sizeof(HLL()) <= 1024 * 32 (32kb)
 */
class HLL
{
private:
    std::mt19937 gen{0}; //NOLINT
    std::uniform_int_distribution<> int_dist{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}; //NOLINT

    int random_int();
    int first_zeros_less_max(unsigned int, int);

private:
    int m_uniq_num = 0;
    double m_error = 0.065;
    double _m;
    int _k;
    int _k_comp;
    double _alpha_m;
    int _boost_m = 200;
    size_t pow_2_32 = 0xFFFFFFFF + 1;
    std::vector<int> _M;

private:
    static size_t const THREADS_NUMBER = 3;
    std::thread threads[THREADS_NUMBER];

public:

    /**
     * standard error = 1.04 / sqrt(1 << k)
     * k - count of bytes for indexing
     * E = (_alpha_m * _m^2) / sum<j> (1 << -M[j])
     * E - unique values
     */
    explicit HLL(double);

    virtual ~HLL();

    void add(int x);

    void add_data(std::vector<int> &data);

    void analyse_portion(const std::vector<int> &data, size_t begin, size_t end);

    int get_uniq_num() const;
};


#endif //HYPERLOGLOG_HLL_H
