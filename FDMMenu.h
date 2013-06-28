//
//  FDMMenu.h
//  ScratJumpers
//
//  Created by firedragonpzy on 13-4-8.
//
//

#ifndef __ScratJumpers__FDMMenu__
#define __ScratJumpers__FDMMenu__

#include "cocos2d.h"
USING_NS_CC;
class FDMMenu : public CCMenu
{
public:
    /** creates an empty CCMenu */
    static FDMMenu* create();
    
    /** creates a CCMenu with it's items */
    static FDMMenu* create(CCMenuItem* item, ...);
    
    /** creates a CCMenu with a CCArray of CCMenuItem objects */
    static FDMMenu* create(CCArray* pArrayOfItems);
    
    static FDMMenu* createWithItems(CCMenuItem* item, va_list args);
    
    static FDMMenu* createWithArray(CCArray* pArrayOfItems);
    
    virtual void ccTouchMoved(CCTouch *touch, CCEvent* event);
};

#endif /* defined(__ScratJumpers__FDMMenu__) */
