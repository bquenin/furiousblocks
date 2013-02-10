//
// Created by bquenin on 1/29/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "CCApplicationEx.h"
#include "Social.h"
#include "AppDelegate.h"
#include "me_pixodro_FuriousBlocks.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

using namespace cocos2d;

CCApplicationEx::CCApplicationEx()
: CCApplication() {
}

void CCApplicationEx::openURL(const std::string& url) {
  JniMethodInfo minfo;

  if (JniHelper::getStaticMethodInfo(minfo, "me/pixodro/FuriousBlocks", "openURL", "(Ljava/lang/String;)V")) {
    jstring StringArg1 = minfo.env->NewStringUTF(url.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
    minfo.env->DeleteLocalRef(StringArg1);
    minfo.env->DeleteLocalRef(minfo.classID);
  }
}

void CCApplicationEx::facebookLogin() {
  JniMethodInfo minfo;

  if (JniHelper::getStaticMethodInfo(minfo, "me/pixodro/FuriousBlocks", "facebookLogin", "()V")) {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
  }
}

void CCApplicationEx::facebookLogout() {
  JniMethodInfo minfo;

  if (JniHelper::getStaticMethodInfo(minfo, "me/pixodro/FuriousBlocks", "facebookLogout", "()V")) {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
  }
}

void CCApplicat ionEx::quit() {
  terminateProcessJNI();
}

std::string CCApplicationEx::getDeviceUID() {
  JniMethodInfo t;

  if (JniHelper::getStaticMethodInfo(t, "me/pixodro/FuriousBlocks", "getDeviceUID", "()Ljava/lang/String;")) {
    jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID);
    t.env->DeleteLocalRef(t.classID);
    CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
    ret->autorelease();
    t.env->DeleteLocalRef(str);
    return ret->m_sString;
  }
  return 0;
}

extern "C" {
  JNIEXPORT void JNICALL Java_me_pixodro_FuriousBlocks_facebookSessionStatusCallback(JNIEnv *env, jobject thiz, jstring sessionStatus, jstring accessToken) {
    AppDelegate::setLoggedIn(JniHelper::jstring2string(sessionStatus) == "OPENED");
    AppDelegate::setAccessToken(JniHelper::jstring2string(accessToken));
    Social::registerPlayer();
  }
}
