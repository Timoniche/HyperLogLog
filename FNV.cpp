#include "FNV.h"

namespace FNV
{
    unsigned int count_element(int val)
    {
        unsigned int hval = 0x811c9dc5;
        hval ^= (unsigned int) val;
        hval *= FNV_32_PRIME;
        return hval;
    }

    unsigned int count_data(int *buf)
    {
        unsigned int hval = 0x811c9dc5;

        while (*buf)
        {
            hval ^= (unsigned int) *buf++;
            hval *= FNV_32_PRIME;
        }

        return hval;
    }
}

