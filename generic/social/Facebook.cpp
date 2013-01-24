//
// Created by bquenin on 1/23/13.
//
//


#include "Facebook.h"
#include "AppDelegate.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/URI.h"
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/DefaultHandler.h"
#include "Poco/JSON/JSONException.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "me_pixodro_FuriousBlocks.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
  std::string g_sessionStatus("no session status");
  std::string g_accessToken("no access token");

  JNIEXPORT void JNICALL Java_me_pixodro_FuriousBlocks_facebookSessionStatusCallback(JNIEnv *env, jobject thiz, jstring sessionStatus, jstring accessToken) {
    g_sessionStatus = JniHelper::jstring2string(sessionStatus);
    g_accessToken = JniHelper::jstring2string(accessToken);
    std::string OPENED("OPENED");
    AppDelegate::setLoggedIn(g_sessionStatus == OPENED);
    CCLOG("sessionStatus = %s", g_sessionStatus.c_str());
    CCLOG("accessToken= %s", g_accessToken.c_str());
  }
}
#endif

void Facebook::logIn() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->onClickLogin();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  JniMethodInfo minfo;

  if(JniHelper::getStaticMethodInfo(minfo,
    "me/pixodro/FuriousBlocks",
    "onClickLogin",
    "()V"))
  {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
  }
#endif
}

void Facebook::logOut() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->onClickLogout();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  JniMethodInfo minfo;

  if(JniHelper::getStaticMethodInfo(minfo,
    "me/pixodro/FuriousBlocks",
    "onClickLogout",
    "()V"))
  {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
  }
#endif
}

void Facebook::getInfo() {
  using namespace Poco;
  try {
    // Target URI
    URI uri("https://graph.facebook.com/me?fields=id,first_name,last_name&access_token=" + AppDelegate::getAccessToken());
    std::string path(uri.getPathEtc());

    // SSL Context
    const Net::Context::Ptr context(new Net::Context(Net::Context::CLIENT_USE, "", "", "", Net::Context::VERIFY_NONE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"));

    // HTTP Session
    Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);

    // Request
    Net::HTTPRequest request(Net::HTTPRequest::HTTP_GET, path, Net::HTTPMessage::HTTP_1_1);
    session.sendRequest(request);

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);
//    std::cout << response.getStatus() << " " << response.getReason() << std::endl;
//    for (auto response_header : response) {
//      std::cout << response_header.first << " = " << response_header.second << std::endl;
//    }

    std::ostringstream responseBody;
    if (response.getStatus() != Net::HTTPResponse::HTTP_UNAUTHORIZED) {
      StreamCopier::copyStream(rs, responseBody);
//      StreamCopier::copyStream(rs, std::cout);
    } else {
      NullOutputStream null;
      StreamCopier::copyStream(rs, null);
      return;
    }

    // Parsing JSON response
    JSON::DefaultHandler handler;
    JSON::Parser parser;

    parser.setHandler(&handler);
    parser.parse(responseBody.str());

    JSON::Object::Ptr jsonResponse = handler.result().extract<JSON::Object::Ptr>();
    std::ostringstream outStream;
    jsonResponse->stringify(outStream, 2);
    CCLOG("json response = %s", outStream.str().c_str());

//    JSON::Array::Ptr data = jsonResponse->getArray("data");

//    std::cout << "array size = " << data->size() << std::endl;
//    for (unsigned int i = 0; i < data->size(); i++) {
//      std::cout << "value[" << i << "] = " << data->getElement<std::string>(i) << std::endl;
//    }

//    // Serialize to string
//    data->stringify(std::cout, 0);
//    std::cout << "test4" << std::endl;

//    std::cout << "output = " << out.str() << std::endl << "done." << std::endl;
  } catch (Exception& exc) {
    CCLOG("error =  %s", exc.displayText().c_str());
  }

//  char ch;
//
//  while (rs) { // in will be false when eof is reached
//    rs.get(ch);
//    if (rs) {
//      std::cout << ch;
//    }
//  }

}
