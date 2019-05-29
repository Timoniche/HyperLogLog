#include "HLL.h"
#include <cmath>

#include <cstddef>
#include <random>
#include <limits>
#include <vector>
#include <thread>
#include <functional>

//______________________________________________________________________________________________________________________
int HLL::random_int()
{
    return int_dist(gen);
}

int HLL::first_zeros_less_max(unsigned int hash, int max)
{
    int r = 1;
    while ((hash & 1) == 0 && r <= max)
    {
        ++r;
        hash >>= 1;
    }
    return r;
}

//______________________________________________________________________________________________________________________
void HLL::add(int x)
{
    unsigned int hash = FNV::count_element(x);
    int j = hash >> _k_comp;
    _M[j] = std::max(_M[j], first_zeros_less_max(hash, _k_comp));
}

void HLL::add_data(std::vector<int> &data)
{
    int size_of_block = data.size() / THREADS_NUMBER;
    for (int i = 0; i < THREADS_NUMBER - 1; i++)
    {
        threads[i] = std::thread(&HLL::analyse_portion, this, std::ref(data), i * size_of_block, (i + 1) * size_of_block + 1);
    }
    int last_index = THREADS_NUMBER - 1;
    threads[last_index] = std::thread(&HLL::analyse_portion, this, std::ref(data), last_index * size_of_block,
                                      data.size());

    for (auto &thread : threads)
    {
        thread.join();
    }
}

void HLL::analyse_portion(const std::vector<int> &data, size_t begin, size_t end)
{
    for (size_t i = begin; i < end; i++)
    {
        add(data[i]);
    }
}

int HLL::get_uniq_num() const
{
    double c = 0;
    for (int i = 0; i < _m; ++i)
    {
        c += double(1) / (1 << _M[i]);
    }
    double E = _alpha_m * _m * _m / c;

    if (E <= double(5) / 2 * _m)
    {
        int V = 0;
        for (int i = 0; i < _m; ++i)
        {
            if (_M[i] == 0)
            {
                ++V;
            }
        }
        if (V > 0)
        {
            E = _m * std::log(_m / V);
        }
    } else if (E > double(1) / 30 * pow_2_32)
    {
        E = -pow_2_32 * std::log(1 - E / pow_2_32);
    }

    return static_cast<int>(E);
}

HLL::HLL(double error) : m_error(error)
{
    _m = 1.04 / m_error * _boost_m;
    _k = static_cast<int>(ceil(std::log2(_m * _m)));
    _k_comp = 32 - _k;
    _m = 1 << _k;
    _alpha_m = _m == 16 ? 0.673
                        : _m == 32 ? 0.697
                                   : _m == 64 ? 0.709
                                              : 0.7213 / (1 + 1.079 / _m);
    _M.assign((size_t) _m, 0);
}

HLL::~HLL() = default;