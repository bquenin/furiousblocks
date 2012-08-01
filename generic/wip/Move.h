#ifndef __Move_H_
#define __Move_H_

#include <cstdint>

class Move {
private:
protected:
public:
  int8_t type = 0;
  Move(int8_t type);
  Move(Move *move);
};

#endif //__Move_H_
