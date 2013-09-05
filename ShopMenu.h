//
//  ShopMenu.h
//  IronPig
//
//  Created by firedragonpzy on 13-9-3.
//
//

#ifndef __IronPig__ShopMenu__
#define __IronPig__ShopMenu__

#include "cocos2d.h"
USING_NS_CC;
#include "ShopItem.h"
class ShopMenu : public CCMenu
{
public:
    /** creates an empty CCMenu */
    static ShopMenu* create();
    
    /** creates a CCMenu with it's items */
    static ShopMenu* create(CCMenuItem* item, ...);
    
    /** creates a CCMenu with a CCArray of CCMenuItem objects */
    static ShopMenu* create(CCArray* pArrayOfItems);
    
    static ShopMenu* createWithItems(CCMenuItem* item, va_list args);
    
    static ShopMenu* createWithArray(CCArray* pArrayOfItems);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    CCMenuItem* itemForTouch(CCTouch * touch);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
private:
     CCMenuItem *m_pLastItem;
};

#endif /* defined(__IronPig__ShopMenu__) */

