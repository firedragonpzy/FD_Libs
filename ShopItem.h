//
//  ShopItem.h
//  IronPig
//
//  Created by firedragonpzy on 13-9-3.
//
//

#ifndef __IronPig__ShopItem__
#define __IronPig__ShopItem__

#include "cocos2d.h"
USING_NS_CC;

class ShopItem : public CCMenuItemSprite {
public:
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static ShopItem * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    virtual void activate();
};

#endif /* defined(__IronPig__ShopItem__) */
