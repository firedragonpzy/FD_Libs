//
//  UtilTools.h
//  ToyGame
//
//  Created by firedragonpzy on 13-1-4.
//
//

#ifndef ToyGame_UtilTools_h
#define ToyGame_UtilTools_h
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "RConfig.h"
#include "DataBase64.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace extension;

class UtilTools
{
public:
    static bool musicState;
    static bool isMusicOpen;

    static void playMusicAndEffect( const char* pszFilePath, bool bLoop )
    {
        setIntegerForKey(XML_MUSIC_STATUS, FDTRUE);
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pszFilePath, bLoop);
        setIntegerForKey(XML_EFFECT_STATUS, FDTRUE);
        UtilTools::musicState = true;
    }
    
    static void stopMusicAndEffect( const char* pszFilePath )
    {
        setIntegerForKey(XML_MUSIC_STATUS, FDFALSE);
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(MUSIC_BG);
        setIntegerForKey(XML_EFFECT_STATUS, FDFALSE);
        UtilTools::musicState = false;
    }
    
    
    static void pauseMusicAndEffect()
    {
        setIntegerForKey(XML_MUSIC_STATUS, FDFALSE);
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        setIntegerForKey(XML_EFFECT_STATUS, FDFALSE);
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        UtilTools::musicState = false;
    }
    
    
    static void resumeMusicAndEffect( const char* pszFilePath, bool bLoop )
    {
		if( UtilTools::isMusicOpen )
		{
            setIntegerForKey(XML_MUSIC_STATUS, FDTRUE);
            setIntegerForKey(XML_EFFECT_STATUS, FDTRUE);
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		}else
		{
			playMusicAndEffect( pszFilePath, bLoop );
            UtilTools::isMusicOpen = true;
		} 
           UtilTools::musicState = true;

    }

	static void playEffect( const char* pszFilePath )
	{
        
        if (getIntegerForKey(XML_EFFECT_STATUS)) {
             SimpleAudioEngine::sharedEngine()->playEffect( std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszFilePath)).c_str() );
        }
	}
    
    
    static int getIntegerForKey(const char* pKey)
    {
        std::string key = pKey;
        key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
//        std::string data = CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str());
          std::string data = CCUserDefault::sharedUserDefault()->getStringForKey(pKey);
        data = ParseData(data);
        CCString *str = CCString::create(data);
        return str->intValue();
    }
    
    static void setIntegerForKey(const char* pKey, int value)
    {
        char buffer[50];
        sprintf(buffer,"%d",value);
        std::string data = buffer;
        std::string key = pKey;
        data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
        key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
//        CCUserDefault::sharedUserDefault()->setStringForKey(key.c_str(), data);
                CCUserDefault::sharedUserDefault()->setStringForKey(pKey, data);
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    static CCScene* getSceneByCCBI( const char * pClassName, CCNodeLoader *pCCNodeLoader, const char *pCCBFileName)
    {
        CCNodeLoaderLibrary *nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        nodeLoaderLibrary->registerCCNodeLoader(pClassName,pCCNodeLoader);
        CCBReader *ccbReader = new CCBReader(nodeLoaderLibrary);
        ccbReader->autorelease();
        CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile(pCCBFileName);
        return pScene;
    }
    
    static CCScene* getSceneAndLayerByCCBI( const char * pClassName, CCNodeLoader *pCCNodeLoader, const char *pCCBFileName,const char * pClassName1, CCNodeLoader *pCCNodeLoader1, const char *pCCBFileName1  )
    {
        CCNodeLoaderLibrary *nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        nodeLoaderLibrary->registerCCNodeLoader(pClassName,pCCNodeLoader);
        nodeLoaderLibrary->registerCCNodeLoader(pClassName1,pCCNodeLoader1);
        CCBReader *ccbReader = new CCBReader(nodeLoaderLibrary);
        ccbReader->autorelease();
        CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile(pCCBFileName);
        CCBReader *ccbReader1 = new CCBReader(nodeLoaderLibrary);
        ccbReader1->autorelease();
        CCLayer *layer = (CCLayer*)ccbReader1->readNodeGraphFromFile(pCCBFileName1);
        CCPoint point = CCDirector::sharedDirector()->getVisibleOrigin();
        layer->setPosition(ccp( point.x, point.y));
        pScene->addChild(layer,1);
        return pScene;
    }
    static CCScene* getSceneAndLayerWithSVByCCBI( const char * pClassName, CCNodeLoader *pCCNodeLoader, const char *pCCBFileName,const char * pClassName1, CCNodeLoader *pCCNodeLoader1, const char *pCCBFileName1, const char * pClassName2,CCNodeLoader *pCCNodeLoader2 )
    {
        
       CCNodeLoaderLibrary *nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        nodeLoaderLibrary->registerCCNodeLoader(pClassName,pCCNodeLoader);
        nodeLoaderLibrary->registerCCNodeLoader(pClassName2,pCCNodeLoader2);
        CCBReader *ccbReader = new CCBReader(nodeLoaderLibrary);
                nodeLoaderLibrary->registerCCNodeLoader(pClassName1,pCCNodeLoader1);
        ccbReader->autorelease();
        CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile(pCCBFileName);
        CCBReader *ccbReader1 = new CCBReader(nodeLoaderLibrary);
        ccbReader1->autorelease();
        CCLayer *layer = (CCLayer*)ccbReader1->readNodeGraphFromFile(pCCBFileName1);
        CCPoint point = CCDirector::sharedDirector()->getVisibleOrigin();
        layer->setPosition(ccp( point.x, point.y));
        pScene->addChild(layer,1);
        return pScene;
    }
};



#endif
