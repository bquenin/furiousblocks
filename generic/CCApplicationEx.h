//
// Created by bquenin on 1/29/13.
//
//

#ifndef __CCApplicationEx_H_
#define __CCApplicationEx_H_

#include <string>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "platform/ios/CCApplication.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCApplication.h"
#endif

class CCApplicationEx : public cocos2d::CCApplication {
public:

  CCApplicationEx();
  virtual ~CCApplicationEx() {};

  static void openURL(const std::string& url);
  static void facebookLogin();
  static void facebookLogout();
  static void quit();
};

#endif //__CCApplicationEx_H_
