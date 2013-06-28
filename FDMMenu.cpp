//
//  FDMMenu.cpp
//  ScratJumpers
//
//  Created by firedragonpzy on 13-4-8.
//
//

#include "FDMMenu.h"

USING_NS_CC;

FDMMenu* FDMMenu::create()
{
    return FDMMenu::create(NULL, NULL);
}


FDMMenu * FDMMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    FDMMenu *pRet = FDMMenu::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;
}


FDMMenu* FDMMenu::createWithItems(CCMenuItem* item, va_list args)
{
    CCArray* pArray = NULL;
    if( item )
    {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
        }
    }
    
    return FDMMenu::createWithArray(pArray);
}


FDMMenu* FDMMenu::createWithArray(CCArray* pArrayOfItems)
{
    FDMMenu *pRet = new FDMMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


FDMMenu* FDMMenu::create(CCArray* pArrayOfItems)
{
    FDMMenu *pRet = new FDMMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


void FDMMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
    CCMenuItem *currentItem = this->itemForTouch(touch);
    if (currentItem != m_pSelectedItem)
    {
        if (m_pSelectedItem)
        {
            m_pSelectedItem->unselected();
        }
        m_pSelectedItem = currentItem;
        if (m_pSelectedItem)
        {
            m_pSelectedItem->selected();
        }
    }
    if (currentItem) {
        currentItem->activate();
    }

}