//
//  FDTimeLayer.h
//  IronPig
//
//  Created by firedragonpzy on 13-6-28.
//
//

#ifndef __IronPig__FDTimeLayer__
#define __IronPig__FDTimeLayer__
#include "cocos2d.h"
#include "RConfig.h"
#include "MainGameScene.h"
USING_NS_CC;

class FDTimeLayer : public CCLayer {
public:
    bool init();
    CC_SYNTHESIZE(int, _m_pTimeFlag, TimeFlag);
    void updateTime(float dt);
    void addTempSprite();
    CCSprite *timeSprite;
    CREATE_FUNC(FDTimeLayer);
};

#endif /* defined(__IronPig__FDTimeLayer__) */
