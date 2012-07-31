#include <cstdint>
#include <cstdlib>
#include "SimpleRNG.h"

SimpleRNG::SimpleRNG(int32_t u)
{
    m_w = u;
}

int32_t SimpleRNG::nextInt()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return abs((m_z << 16) + m_w);
}

double SimpleRNG::nextDouble()
{
    int32_t u = nextInt();
    return (u + 1.0) * 2.328306435454494e-10;
}
