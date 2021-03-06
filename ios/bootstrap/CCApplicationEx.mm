//
// Created by bquenin on 1/29/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#import "CCApplicationEx.h"
#import <FacebookSDK/FacebookSDK.h>
#import "AppController.h"
#import <sys/socket.h> // Per msqr
#import "Assets.h"
#include "AppDelegate.h"
#import <sys/sysctl.h>
#import <net/if.h>
#import <net/if_dl.h>

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
  AppDelegate::setLoggedIn(false);
  AppDelegate::setAccessToken("none");
  [FBSession.activeSession closeAndClearTokenInformation];
}

void CCApplicationEx::quit() {
  exit(0);
}

std::string CCApplicationEx::getDeviceUID() {
  int mib[6];
  size_t len;
  void* buf;
  unsigned char* ptr;
  struct if_msghdr* ifm;
  struct sockaddr_dl* sdl;

  mib[0] = CTL_NET;
  mib[1] = AF_ROUTE;
  mib[2] = 0;
  mib[3] = AF_LINK;
  mib[4] = NET_RT_IFLIST;

  if ((mib[5] = if_nametoindex("en0")) == 0) {
    printf("Error: if_nametoindex error\n");
    return NULL;
  }

  if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
    printf("Error: sysctl, take 1\n");
    return NULL;
  }

  if ((buf = malloc(len)) == NULL) {
    printf("Could not allocate memory. error!\n");
    return NULL;
  }

  if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
    printf("Error: sysctl, take 2");
    free(buf);
    return NULL;
  }

  ifm = (struct if_msghdr*) buf;
  sdl = (struct sockaddr_dl*) (ifm + 1);
  ptr = (unsigned char*) LLADDR(sdl);
  std::string outString = CCString::createWithFormat("%02X:%02X:%02X:%02X:%02X:%02X", *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5))->getCString();
  free(buf);

  return outString;
}
