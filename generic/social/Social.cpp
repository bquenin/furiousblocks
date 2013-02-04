//
// Created by bquenin on 1/23/13.
//


#include "Social.h"
#include "AppDelegate.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/URI.h"
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/MediaType.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/DefaultHandler.h"
#include "Poco/JSON/JSONException.h"

using namespace Poco;

const std::string Social::PIXODROME_SERVER = "http://pixodro.me/";
//const std::string Social::PIXODROME_SERVER = "http://192.168.0.11:9000/";

void Social::registerPlayer() {
  try {
    // SSL Context
    const Net::Context::Ptr context(new Net::Context(Net::Context::CLIENT_USE, "", "", "", Net::Context::VERIFY_NONE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"));

    // Target URI
    URI uri("https://graph.facebook.com/me?fields=id,first_name,last_name,friends.fields(first_name,last_name)&access_token=" + AppDelegate::getAccessToken());
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);

    // Request
    Net::HTTPRequest request(Net::HTTPRequest::HTTP_GET, path, Net::HTTPMessage::HTTP_1_1);
    session.sendRequest(request);

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);
    std::ostringstream responseBody;
    if (response.getStatus() != Net::HTTPResponse::HTTP_UNAUTHORIZED) {
      StreamCopier::copyStream(rs, responseBody);
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

    JSON::Object::Ptr facebookResponse = handler.result().extract<JSON::Object::Ptr>();
    facebookResponse->getObject("friends")->remove("paging");

#if 0
    std::ostringstream out;
    facebookResponse->stringify(out, 2);
    CCLOG("response = %s", out.str().c_str());
#endif

    AppDelegate::setFacebookId(facebookResponse->get("id"));

    // Get or create the player
    createOrUpdatePlayer(facebookResponse->get("id"), facebookResponse);
  } catch (Exception& exc) {
    CCLOG("error in registerPlayer = %s", exc.displayText().c_str());
  }
}

void Social::createOrUpdatePlayer(const std::string& facebookId, JSON::Object::Ptr facebookResponse) {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "players/" + facebookId);
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    Net::HTTPRequest request(Net::HTTPRequest::HTTP_POST, path, Net::HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.setChunkedTransferEncoding(true);
    facebookResponse->stringify(session.sendRequest(request));

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);

    if (response.getStatus() == Net::HTTPResponse::HTTP_BAD_REQUEST) {
      std::ostringstream error;
      StreamCopier::copyStream(rs, error);
      CCLOG("Bad request: %s", error.str().c_str());
      return;
    }
  } catch (Exception& exc) {
    CCLOG("%s", exc.displayText().c_str());
  }
}

void Social::submitScore(uint64_t score, uint32_t duration) {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "scores/" + AppDelegate::getFacebookId());
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("score", score);
    jsonRequest.set("duration", duration);

    Net::HTTPRequest request(Net::HTTPRequest::HTTP_POST, path, Net::HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(request));

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);

    if (response.getStatus() == Net::HTTPResponse::HTTP_BAD_REQUEST) {
      std::ostringstream error;
      StreamCopier::copyStream(rs, error);
      CCLOG("Bad request: %s", error.str().c_str());
      return;
    } else if (response.getStatus() == Net::HTTPResponse::HTTP_NOT_FOUND) {
      CCLOG("Not found.");
      return;
    }
  } catch (Exception& exc) {
    CCLOG("%s", exc.displayText().c_str());
  }
}

void Social::getMyScores() {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "scores/" + AppDelegate::getFacebookId());
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("type", "mines");

    Net::HTTPRequest request(Net::HTTPRequest::HTTP_GET, path, Net::HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(request));

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);

    if (response.getStatus() == Net::HTTPResponse::HTTP_BAD_REQUEST) {
      std::ostringstream error;
      StreamCopier::copyStream(rs, error);
      CCLOG("Bad request: %s", error.str().c_str());
      return;
    } else if (response.getStatus() == Net::HTTPResponse::HTTP_NOT_FOUND) {
      CCLOG("Not found.");
      return;
    }
    std::ostringstream responseBody;
    StreamCopier::copyStream(rs, responseBody);
    CCLOG("response body = %s", responseBody.str().c_str());
  } catch (Exception& exc) {
    CCLOG("%s", exc.displayText().c_str());
  }
}

void Social::getFriendsScores() {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "scores/" + AppDelegate::getFacebookId());
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("type", "friends");

    Net::HTTPRequest request(Net::HTTPRequest::HTTP_GET, path, Net::HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(request));

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);

    if (response.getStatus() == Net::HTTPResponse::HTTP_BAD_REQUEST) {
      std::ostringstream error;
      StreamCopier::copyStream(rs, error);
      CCLOG("Bad request: %s", error.str().c_str());
      return;
    } else if (response.getStatus() == Net::HTTPResponse::HTTP_NOT_FOUND) {
      CCLOG("Not found.");
      return;
    }
    std::ostringstream responseBody;
    StreamCopier::copyStream(rs, responseBody);
    CCLOG("response body = %s", responseBody.str().c_str());
  } catch (Exception& exc) {
    CCLOG("%s", exc.displayText().c_str());
  }
}

void Social::getWorldScores() {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "scores/" + AppDelegate::getFacebookId());
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("type", "world");

    Net::HTTPRequest request(Net::HTTPRequest::HTTP_GET, path, Net::HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(request));

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);

    if (response.getStatus() == Net::HTTPResponse::HTTP_BAD_REQUEST) {
      std::ostringstream error;
      StreamCopier::copyStream(rs, error);
      CCLOG("Bad request: %s", error.str().c_str());
      return;
    } else if (response.getStatus() == Net::HTTPResponse::HTTP_NOT_FOUND) {
      CCLOG("Not found.");
      return;
    }
    std::ostringstream responseBody;
    StreamCopier::copyStream(rs, responseBody);
    CCLOG("response body = %s", responseBody.str().c_str());
  } catch (Exception& exc) {
    CCLOG("%s", exc.displayText().c_str());
  }
}

