//
//  testAppDelegate.h
//  test
//
//  Created by Bertrand Quenin on 01/07/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"

#include "Assets.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class AppDelegate : private cocos2d::CCApplication {
public:
  static Assets assets;

  AppDelegate();
  virtual ~AppDelegate();

  static void setGamesLeft(int32_t gamesLeft);
  static int32_t getGamesLeft();

  static void setMusicOn(bool musicOn);
  static bool isMusicOn();

  static void setLoggedIn(bool loggedIn);
  static bool isLoggedIn();

  static void setAccessToken(const std::string& accessToken);
  static std::string getAccessToken();

  static void setFacebookId(const std::string& facebookId);
  static std::string getFacebookId();


  /**
  @brief    Implement CCDirector and CCScene init code here.
  @return true    Initialize success, app continue.
  @return false   Initialize failed, app terminate.
  */
  virtual bool applicationDidFinishLaunching();

  /**
  @brief  The function be called when the application enter background
  @param  the pointer of the application
  */
  virtual void applicationDidEnterBackground();

  /**
  @brief  The function be called when the application enter foreground
  @param  the pointer of the application
  */
  virtual void applicationWillEnterForeground();

};

#endif // _APP_DELEGATE_H_

