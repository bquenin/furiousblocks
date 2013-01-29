//
// Created by bquenin on 1/23/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Social_H_
#define __Social_H_

#include <iostream>

class Social {
private:
  static const std::string PIXODROME_SERVER;

public:
  static void registerPlayer();
  static void createOrUpdatePlayer(const std::string& facebookId, const std::string& firstName, const std::string& lastName, const std::string& accessToken);
  static void submitScore(uint64_t score);
  static void getMyScores();
  static void getFriendsScores();
  static void getWorldScores();
};

#endif //__Social_H_
