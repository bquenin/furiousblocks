//
// Created by bquenin on 1/23/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Social_H_
#define __Social_H_

#include <iostream>
#include <Poco/SharedPtr.h>
#include <Poco/JSON/Object.h>
#include "ScoreEntry.h"

class Social {
private:
  static const std::string PIXODROME_SERVER;

public:
  static void registerPlayer();
  static void createOrUpdatePlayer(std::string const & facebookId, Poco::SharedPtr <Poco::JSON::Object> facebookResponse);
  static void submitScore(uint64_t score, uint32_t duration);
  static std::vector<ScoreEntry> getMyScores();
  static std::vector<ScoreEntry> getFriendsScores();
  static std::vector<ScoreEntry> getWorldScores();
};

#endif //__Social_H_
