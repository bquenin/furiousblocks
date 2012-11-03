#ifndef __TextToType_H_
#define __TextToType_H_

#include <string>

class TextToType {
private:
  std::string text;

protected:
public:
  TextToType();
  std::string getText();
  void setText(std::string text);
};

#endif //__TextToType_H_
