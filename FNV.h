#ifndef HYPERLOGLOG_FNV_H
#define HYPERLOGLOG_FNV_H

namespace FNV
{
    namespace
    {
       const unsigned FNV_32_PRIME = 0x01000193;
    }

    unsigned int count_element(int val);

    unsigned int count_data(int *buf);
}

#endif //HYPERLOGLOG_FNV_H
