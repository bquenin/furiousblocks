//
// Created by bquenin on 1/29/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "CCApplicationEx.h"
#include "Social.h"
#include "AppDelegate.h"

using namespace cocos2d;

CCApplicationEx::CCApplicationEx()
: CCApplication() {
}

void CCApplicationEx::openURL(const std::string& url) {
}

void CCApplicationEx::facebookLogin() {
}

void CCApplicationEx::facebookLogout() {
}

void CCApplicationEx::quit() {
    exit(0);
}

std::string CCApplicationEx::getDeviceUID() {
    return "linux";
}
