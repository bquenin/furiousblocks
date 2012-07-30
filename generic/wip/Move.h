#ifndef __Move_H_
#define __Move_H_

#include <cstdint>

using namespace std;

class Move {
private:
  int8_t type = 0;

protected:
public:
  Move(int8_t type);
  Move(Move& move);
  int8_t getType();
};

#endif //__Move_H_
