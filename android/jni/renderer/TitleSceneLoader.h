//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __TitleSceneLoader_H_
#define __TitleSceneLoader_H_

#include <iostream>
#include "CCLayerLoader.h"
#include "TitleScene.h"

class TitleSceneLoader : public cocos2d::extension::CCLayerLoader {
public:
  CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TitleSceneLoader, loader);

protected:
  CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TitleScene);
};

#endif //__TitleSceneLoader_H_
