//
//  ShopMenu.cpp
//  IronPig
//
//  Created by firedragonpzy on 13-9-3.
//
//

#include "ShopMenu.h"

USING_NS_CC;

ShopMenu* ShopMenu::create()
{
    return ShopMenu::create(NULL, NULL);
}


ShopMenu * ShopMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    ShopMenu *pRet = ShopMenu::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;
}


ShopMenu* ShopMenu::createWithItems(CCMenuItem* item, va_list args)
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
    
    return ShopMenu::createWithArray(pArray);
}


ShopMenu* ShopMenu::createWithArray(CCArray* pArrayOfItems)
{
    ShopMenu *pRet = new ShopMenu();
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


ShopMenu* ShopMenu::create(CCArray* pArrayOfItems)
{
    ShopMenu *pRet = new ShopMenu();
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

void ShopMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
}


bool ShopMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !isEnabled())
    {
        return false;
    }
    if (!isEnabled()) {
        return true;
    }
    
    for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }

    m_pSelectedItem = this->itemForTouch(touch);
    
   
    if (m_pSelectedItem)
    {
        
        m_eState = kCCMenuStateTrackingTouch;
        if (!m_pSelectedItem->isEnabled()) {
            return true;
        }
        m_pSelectedItem->selected();
        return true;
    }
    return false;
}

void ShopMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    m_pLastItem = m_pSelectedItem;
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
    ((ShopItem*)m_pSelectedItem)->activate();
    m_eState = kCCMenuStateWaiting;
}

CCMenuItem* ShopMenu::itemForTouch(CCTouch *touch)
{
    
    CCPoint touchLocation = touch->getLocation();
    
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
            if (pChild && pChild->isVisible())
            {
                CCPoint local = pChild->convertToNodeSpace(touchLocation);
                CCRect r = pChild->rect();
                r.origin = CCPointZero;
                
                if (r.containsPoint(local))
                {
                    if ( m_pLastItem && m_pLastItem->isEnabled()) {
                        m_pLastItem->unselected();
                    }
                    return pChild;
                }
            }
        }
    }
    
    return NULL;
}

