//
//  FDTinyXML2.cpp
//  Runner
//
//  Created by firedragonpzy on 13-5-21.
//
//

#include "FDTinyXML2.h"
#define FDTinyXML2_ROOT_NAME    "firedragonpzy"

#define XML_FILE_NAME "firedragonpzy.xml"
#define XML_FIRST_NODE "grounds"
#define XML_SECOND_NODE "barriers"

bool FDTinyXML2::init()
{
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		m_sFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(XML_FILE_NAME);
	}else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		m_sFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(XML_FILE_NAME);
	}else
	{
       		 m_sFilePath = CCFileUtils::sharedFileUtils()->getWritablePath()  + XML_FILE_NAME;
	}
    return true;
}


// Determine if xml exists.
bool FDTinyXML2::isXMLFileExist()
{
    CCLog("%s",m_sFilePath.c_str());
    FILE *fp = fopen(m_sFilePath.c_str(), "r");
    bool bRet = false;
    if (fp) {
        bRet = true;
        fclose(fp);
    }
    return bRet;
}


bool FDTinyXML2::readXMLToArray(cocos2d::CCArray *&array,cocos2d::CCArray *&array1)
{
    CCLog("%s",m_sFilePath.c_str());
    bool bRet = false;
    
    if (isXMLFileExist()) {    
        do {           
            tinyxml2::XMLDocument *xmlDoc = new tinyxml2::XMLDocument();           
            //            const XMLAttribute *curAttribute = NULL;          
            unsigned long nSize;           
            const char* xmlBuffer = (const char*)CCFileUtils::sharedFileUtils()->getFileData(m_sFilePath.c_str(), "rb", &nSize);
            
            if (NULL == xmlBuffer) {               
                return false;
            }
            
            xmlDoc->Parse(xmlBuffer);
            
            delete [] xmlBuffer;
            
            XMLElement *rootNode = xmlDoc->RootElement();
            
            if (NULL == rootNode) {   
                return false;
            }
            
            // first element
            
            XMLElement *firstNode = rootNode->FirstChildElement();
            
            if (NULL == firstNode) {
                return false;
            }
            
            XMLElement *subFirstNode = firstNode->FirstChildElement();
            
            if (NULL == subFirstNode) {
                return false;
            }
            
            
            
            if (strncmp(firstNode->Name(),XML_FIRST_NODE,strlen(XML_FIRST_NODE)) == 0)  {
                groundNodeToArray(subFirstNode,array);
            }else if (strncmp(firstNode->Name(),XML_SECOND_NODE,strlen(XML_SECOND_NODE)) == 0)
            {
                eleNodeToArray(subFirstNode, array1);
            }
            
            // next element
            
            XMLElement *secondNode = firstNode->NextSiblingElement();
            
            if (NULL == secondNode) {
                return true;
            }
            
            XMLElement *subSecondNode = secondNode->FirstChildElement();
            
            if (NULL == subSecondNode) {
                return true;
            }
            
            
            
            if (strncmp(secondNode->Name(),XML_FIRST_NODE,strlen(XML_FIRST_NODE)) == 0)  {
                groundNodeToArray(subSecondNode,array);
            }else if (strncmp(secondNode->Name(),XML_SECOND_NODE,strlen(XML_SECOND_NODE)) == 0)
            {
                eleNodeToArray(subSecondNode, array1);  
            }
            
        } while (0);
               
        bRet = true;
        
    }else    
    { 
        bRet = false;  
    }
    
    return bRet;
}


void FDTinyXML2::groundNodeToArray(XMLElement *ground,CCArray *&array)
{
    
    const XMLAttribute *curAttribute = NULL;
    
    TempObject *obj = NULL;
    
    GroundBarrierStruct groundStruct;
    
    while (NULL != ground) {
        curAttribute = ground->FirstAttribute();
        
        if (strncmp(curAttribute->Name(), XML_POSX,strlen(XML_POSX)) == 0)  {
            groundStruct.posx = atof(curAttribute->Value());
        }
        
        groundStruct.bType = ground->Name();
        
        obj = TempObject::create();
        
        while (NULL != curAttribute) {
            
            if (strncmp(curAttribute->Name(), XML_POSX,strlen(XML_POSX)) == 0)  {
                groundStruct.posx = atof(curAttribute->Value());
            }else if (strncmp(curAttribute->Name(), XML_POSY,strlen(XML_POSY)) == 0)
            {
                groundStruct.posy = atof(curAttribute->Value());
            }else if (strncmp(curAttribute->Name(), XML_FLAG,strlen(XML_FLAG)) == 0)
            {
                groundStruct.flag = atoi(curAttribute->Value());
            }
            
            obj->setGroundBarrier(groundStruct);
            
            curAttribute = curAttribute->Next();
            
        }
        
        array->addObject(obj);
        
        ground = ground->NextSiblingElement();
        
    }
    
}





void FDTinyXML2::eleNodeToArray(tinyxml2::XMLElement *ele, cocos2d::CCArray *&array1)
{
    EleBarrierStuct eleStruct;
    TempObject *obj = NULL;
    
    const XMLAttribute *curAttribute = NULL;
    
    while (NULL != ele) {
        
        curAttribute = ele->FirstAttribute();
        
        eleStruct.bType = ele->Name();
        
        obj = TempObject::create();
        
        while (NULL != curAttribute) {
            if (strncmp(curAttribute->Name(), XML_POSX,strlen(XML_POSX)) == 0) {
                eleStruct.posx = atof(curAttribute->Value());
            }else if (strncmp(curAttribute->Name(), XML_POSY, strlen(XML_POSY)) == 0)
            {
                eleStruct.posy = atof(curAttribute->Value());
            }else if (strncmp(curAttribute->Name(), XML_FLAG, strlen(XML_FLAG)) == 0)
            {
                eleStruct.flag = atoi(curAttribute->Value());
            }
            
            obj->setEleBarrier(eleStruct);
            
            curAttribute = curAttribute->Next();
            
        }
        
        array1->addObject(obj);
        
        ele = ele->NextSiblingElement();
        
    }
    
}

