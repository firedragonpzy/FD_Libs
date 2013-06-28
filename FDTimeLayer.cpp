//
//  FDTimeLayer.cpp
//  IronPig
//
//  Created by firedragonpzy on 13-6-28.
//
//

#include "FDTimeLayer.h"
bool FDTimeLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        _m_pTimeFlag = 1;
        bRet = true;
    } while (0);
    return bRet;
}



void FDTimeLayer::updateTime(float dt)
{
    if (_m_pTimeFlag < 3) {
        _m_pTimeFlag++;
        char temp[32];
        sprintf(temp, "resume/t%d.png",_m_pTimeFlag);
        CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(temp);
        CCSize conSize = texture->getContentSize();
        timeSprite->setTexture(texture);
        timeSprite->setTextureRect(CCRectMake(0, 0, conSize.width, conSize.height));
        
    }else
    {
        _m_pTimeFlag = 1;
        MainGameScene *mainGame = (MainGameScene*)CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0);
        this->removeFromParentAndCleanup(true);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(RESUME_FIR);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(RESUME_SEC);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(RESUME_TIR);
        mainGame->showUIMenu();
        mainGame->onEnter();
        this->unschedule(schedule_selector(FDTimeLayer::updateTime));
    }
}


void FDTimeLayer::addTempSprite()
{
    _m_pTimeFlag = 1;
    timeSprite = CCSprite::create(RESUME_FIR);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    timeSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(timeSprite,900);
    this->schedule(schedule_selector(FDTimeLayer::updateTime),1);
//    UtilTools::playEffect(EFFECT_TIME123);
}