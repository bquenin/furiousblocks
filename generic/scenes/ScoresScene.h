//
// Created by tsug on 04/07/12.
//



#ifndef __ScoresScene_H_
#define __ScoresScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ScoreEntry.h"
#include "SimpleRNG.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class ScoresScene : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate {
private:
  enum class ScoresState {
    myself,
    friends,
    world
  };

  ScoresState state;
  static std::vector<ScoreEntry> scores;
  CCTableView* tableView;
  CCTableViewCell* myself;
  SimpleRNG random;

public:
  ScoresScene();

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene* scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(ScoresScene);

  bool init();
  void backToTitleAction(CCObject* sender);
  void yoursAction(CCObject* sender);
  void friendsAction(CCObject* sender);
  void worldAction(CCObject* sender);
  void update(float dt);

  virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {
  };
  virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {
  }
  virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
  virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView* table);
  virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table, unsigned int idx);
  virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView* table);
};

#endif //__ScoresScene_H_
