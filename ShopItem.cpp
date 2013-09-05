//
//  ShopItem.cpp
//  IronPig
//
//  Created by firedragonpzy on 13-9-3.
//
//

#include "ShopItem.h"

ShopItem * ShopItem::create(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
    ShopItem *pRet = new ShopItem();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
    pRet->autorelease();
    return pRet;
}

void ShopItem::activate()
{
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(this);
    }
    
    if (kScriptTypeNone != m_eScriptType)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeMenuItemEvent(this);
    }
}
