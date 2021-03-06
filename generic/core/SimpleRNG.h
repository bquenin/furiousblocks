#ifndef __SimpleRNG_H_
#define __SimpleRNG_H_

#include <cstdint>

class SimpleRNG {
private:
  int32_t m_w;
  int32_t m_z;

public:
  SimpleRNG(int32_t u = 521288629);
  int32_t nextInt();
  double nextDouble();
};

#endif //__SimpleRNG_H_
