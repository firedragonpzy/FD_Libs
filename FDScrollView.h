//
//  FDScrollView.h
//  CKCastle
//
//  Created by firedragonpzy on 13-1-24.
//
//

#ifndef __CKCastle__FDScrollView__
#define __CKCastle__FDScrollView__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "UtilTools.h"
#include "MainGameURLayer.h"
#include "ToyMenuSprite.h"
class FDScrollView : public CCScrollView{
public:
    static FDScrollView* create(CCSize size, CCNode* container = NULL);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void onEnter();
    void updateInset();
    void setContentSize(const CCSize & size);
    void setZoomScale(float s);
    void deaccelerateScrolling(float dt);
    bool initWithViewSize(CCSize size, CCNode* container = NULL);
};

#endif /* defined(__CKCastle__FDScrollView__) */
