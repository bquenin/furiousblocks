//
// Created by bquenin on 2/4/13.
//


#include "ScoreEntry.h"

ScoreEntry::ScoreEntry()
: firstName("")
, lastName("")
, score("")
, level("")
, time("") {
}

ScoreEntry::ScoreEntry(const JSON::Object::Ptr json) {
  firstName = json->get("firstName").extract<std::string>().c_str();
  lastName = json->get("lastName").extract<std::string>().c_str();
  score = json->get("score").extract<std::string>().c_str();
  level = json->get("level").extract<std::string>().c_str();
  time = json->get("time").extract<std::string>().c_str();
}

ScoreEntry::~ScoreEntry() {
}
