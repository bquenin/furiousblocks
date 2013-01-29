//
// Created by bquenin on 1/29/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "CCApplicationEx.h"
#import <FacebookSDK/FacebookSDK.h>
#import "AppController.h"

CCApplicationEx::CCApplicationEx()
: CCApplication() {
}

void CCApplicationEx::openURL(const std::string& url) {
  [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]]];
}

void CCApplicationEx::facebookLogin() {
  // FBSample logic
  // The user has initiated a login, so call the openSession method.
  id <UIApplicationDelegate> appDelegate = [UIApplication sharedApplication].delegate;
  [appDelegate openSessionWithAllowLoginUI:YES];
}

void CCApplicationEx::facebookLogout() {
  [FBSession.activeSession closeAndClearTokenInformation];
}

void CCApplicationEx::quit() {
  exit(0);
}

