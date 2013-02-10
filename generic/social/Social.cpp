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
//const std::string Social::PIXODROME_SERVER = "http://pixodro.me:9000/";
//const std::string Social::PIXODROME_SERVER = "http://192.168.0.11:9000/";

bool Social::likesFuriousBlocks() {
  try {
    // SSL Context
    const Net::Context::Ptr context(new Net::Context(Net::Context::CLIENT_USE, "", "", "", Net::Context::VERIFY_NONE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"));

    // Target URI
    URI uri("https://graph.facebook.com/me/likes/422411451165165?access_token=" + AppDelegate::getAccessToken());
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
      return 0;
    }

    // Parsing JSON response
    JSON::DefaultHandler handler;
    JSON::Parser parser;

    parser.setHandler(&handler);
    parser.parse(responseBody.str());

    JSON::Object::Ptr facebookResponse = handler.result().extract<JSON::Object::Ptr>();

#if DEBUG
    std::ostringstream out;
    facebookResponse->stringify(out, 2);
    CCLOG("response = %s", out.str().c_str());
#endif
    return facebookResponse->getArray("data")->size() != 0;
  } catch (Exception& exc) {
    CCLOG("error in likesCount = %s", exc.displayText().c_str());
  }
  return false;
}

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

#if DEBUG
    std::ostringstream out;
    facebookResponse->stringify(out, 2);
    CCLOG("response = %s", out.str().c_str());
#endif

    AppDelegate::setFacebookId(facebookResponse->get("id"));
    AppDelegate::setFirstName(facebookResponse->get("first_name"));
    AppDelegate::setLastName(facebookResponse->get("last_name"));

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

void Social::submitScore(uint64_t score, uint32_t level, uint32_t time) {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "scores/" + AppDelegate::getFacebookId());
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("score", score);
    jsonRequest.set("level", level);
    jsonRequest.set("time", time);

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

std::vector<ScoreEntry> Social::getMyScores() {
  std::vector<ScoreEntry> scores;
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
      return scores;
    } else if (response.getStatus() == Net::HTTPResponse::HTTP_NOT_FOUND) {
      CCLOG("Not found.");
      return scores;
    }

    std::ostringstream responseBody;
    StreamCopier::copyStream(rs, responseBody);

#if DEBUG
    CCLOG("mines = %s", responseBody.str().c_str());
#endif

    // Parsing JSON response
    JSON::DefaultHandler handler;
    JSON::Parser parser;

    parser.setHandler(&handler);
    parser.parse(responseBody.str());

    JSON::Array::Ptr scoreArray = handler.result().extract<JSON::Object::Ptr>()->getArray("data");

    for (Dynamic::Var score : *scoreArray) {
      ScoreEntry entry(score.extract<JSON::Object::Ptr>());
      scores.push_back(entry);
    }
  } catch (Exception& exc) {
    CCLOG("Exception %s", exc.displayText().c_str());
  }
  return scores;
}

std::vector<ScoreEntry> Social::getFriendsScores() {
  std::vector<ScoreEntry> scores;
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
      return scores;
    } else if (response.getStatus() == Net::HTTPResponse::HTTP_NOT_FOUND) {
      CCLOG("Not found.");
      return scores;
    }

    std::ostringstream responseBody;
    StreamCopier::copyStream(rs, responseBody);

#if DEBUG
    CCLOG("friends = %s", responseBody.str().c_str());
#endif

    // Parsing JSON response
    JSON::DefaultHandler handler;
    JSON::Parser parser;

    parser.setHandler(&handler);
    parser.parse(responseBody.str());

    JSON::Array::Ptr scoreArray = handler.result().extract<JSON::Object::Ptr>()->getArray("data");

    for (Dynamic::Var score : *scoreArray) {
      ScoreEntry entry(score.extract<JSON::Object::Ptr>());
      scores.push_back(entry);
    }
  } catch (Exception& exc) {
    CCLOG("Exception %s", exc.displayText().c_str());
  }
  return scores;
}

std::vector<ScoreEntry> Social::getWorldScores() {
  std::vector<ScoreEntry> scores;
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
      return scores;
    } else if (response.getStatus() == Net::HTTPResponse::HTTP_NOT_FOUND) {
      CCLOG("Not found.");
      return scores;
    }

    std::ostringstream responseBody;
    StreamCopier::copyStream(rs, responseBody);

#if DEBUG
    CCLOG("world = %s", responseBody.str().c_str());
#endif

    // Parsing JSON response
    JSON::DefaultHandler handler;
    JSON::Parser parser;

    parser.setHandler(&handler);
    parser.parse(responseBody.str());

    JSON::Array::Ptr scoreArray = handler.result().extract<JSON::Object::Ptr>()->getArray("data");

    for (Dynamic::Var score : *scoreArray) {
      ScoreEntry entry(score.extract<JSON::Object::Ptr>());
      scores.push_back(entry);
    }
  } catch (Exception& exc) {
    CCLOG("Exception %s", exc.displayText().c_str());
  }
  return scores;
}

uint32_t Social::gamesLeft() {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "devices");
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("id", AppDelegate::getDeviceUID());

    Net::HTTPRequest httpRequest(Net::HTTPRequest::HTTP_GET, path, Net::HTTPMessage::HTTP_1_1);
    httpRequest.setContentType("application/json");
    httpRequest.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(httpRequest));

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);
    std::ostringstream responseBody;
    if (response.getStatus() != Net::HTTPResponse::HTTP_UNAUTHORIZED) {
      StreamCopier::copyStream(rs, responseBody);
    } else {
      NullOutputStream null;
      StreamCopier::copyStream(rs, null);
      return 0;
    }

#if DEBUG
    CCLOG("response = %s", responseBody.str().c_str());
#endif

    // Parsing JSON response
    JSON::DefaultHandler handler;
    JSON::Parser parser;

    parser.setHandler(&handler);
    parser.parse(responseBody.str());

    JSON::Object::Ptr jsonResponse = handler.result().extract<JSON::Object::Ptr>();

#if DEBUG
    std::ostringstream out;
    jsonResponse->stringify(out, 2);
    CCLOG("response = %s", out.str().c_str());
#endif

    return jsonResponse->get("gamesLeft");
  } catch (Exception& exc) {
    CCLOG("error in gamesLeft = %s", exc.displayText().c_str());
  }
  return 0;
}

uint32_t Social::gamesPerDay() {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "devices");
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("id", AppDelegate::getDeviceUID());

    Net::HTTPRequest httpRequest(Net::HTTPRequest::HTTP_GET, path, Net::HTTPMessage::HTTP_1_1);
    httpRequest.setContentType("application/json");
    httpRequest.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(httpRequest));

    // Response
    Net::HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);
    std::ostringstream responseBody;
    if (response.getStatus() != Net::HTTPResponse::HTTP_UNAUTHORIZED) {
      StreamCopier::copyStream(rs, responseBody);
    } else {
      NullOutputStream null;
      StreamCopier::copyStream(rs, null);
      return 0;
    }

#if DEBUG
    CCLOG("response = %s", responseBody.str().c_str());
#endif

    // Parsing JSON response
    JSON::DefaultHandler handler;
    JSON::Parser parser;

    parser.setHandler(&handler);
    parser.parse(responseBody.str());

    JSON::Object::Ptr jsonResponse = handler.result().extract<JSON::Object::Ptr>();

#if DEBUG
    std::ostringstream out;
    jsonResponse->stringify(out, 2);
    CCLOG("response = %s", out.str().c_str());
#endif

    return jsonResponse->get("gamesPerDay");
  } catch (Exception& exc) {
    CCLOG("error in gamesLeft = %s", exc.displayText().c_str());
  }
  return 0;
}


void Social::beginGame() {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "devices");
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("id", AppDelegate::getDeviceUID());

    Net::HTTPRequest httpRequest(Net::HTTPRequest::HTTP_POST, path, Net::HTTPMessage::HTTP_1_1);
    httpRequest.setContentType("application/json");
    httpRequest.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(httpRequest));

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
  } catch (Exception& exc) {
    CCLOG("error in beginGame = %s", exc.displayText().c_str());
  }
}

void Social::giveLikeBonus() {
  try {
    // Target URI
    URI uri(PIXODROME_SERVER + "devices");
    std::string path(uri.getPathEtc());

    // HTTP Session
    Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // Request
    JSON::Object jsonRequest;
    jsonRequest.set("id", AppDelegate::getDeviceUID());
    jsonRequest.set("bonus", AppDelegate::getDeviceUID());

    Net::HTTPRequest httpRequest(Net::HTTPRequest::HTTP_POST, path, Net::HTTPMessage::HTTP_1_1);
    httpRequest.setContentType("application/json");
    httpRequest.setChunkedTransferEncoding(true);
    jsonRequest.stringify(session.sendRequest(httpRequest));

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
  } catch (Exception& exc) {
    CCLOG("error in beginGame = %s", exc.displayText().c_str());
  }
}
