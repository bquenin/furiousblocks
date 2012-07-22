#include "SimpleRNG.h"
using namespace std;

SimpleRNG::SimpleRNG(int u)
:m_w(521288629), m_z(362436069)
{
    m_w = u;
}

int SimpleRNG::nextInt()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return Math->abs((m_z << 16) + m_w);
}

double SimpleRNG::nextDouble()
{
    int u = nextInt();
    return (u + 1.0) * 2.328306435454494e-10;
}
