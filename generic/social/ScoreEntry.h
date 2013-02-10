//
// Created by bquenin on 2/4/13.
//



#ifndef __ScoreEntry_H_
#define __ScoreEntry_H_

#include <iostream>
#include <Poco/JSON/Object.h>

using namespace Poco;

class ScoreEntry {
public:
  std::string firstName;
  std::string lastName;
  std::string score;
  std::string time;
  std::string level;

  ScoreEntry();
  ScoreEntry(JSON::Object::Ptr json);
  ~ScoreEntry();
};

#endif //__ScoreEntry_H_
