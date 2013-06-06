//
//  FDTinyXML2.h
//  Runner
//
//  Created by firedragonpzy on 13-5-21.
//
//

#ifndef __Runner__FDTinyXML2__
#define __Runner__FDTinyXML2__

#include "support/tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "platform/CCFileUtils.h"
#include "TempObject.h"
#include "RConfig.h"
#include <fstream>
using namespace tinyxml2;
using namespace std;

class FDTinyXML2 : public CCObject {
    
public:
    bool init();
    CREATE_FUNC(FDTinyXML2);
    
    bool readXMLToArray(CCArray* &array,cocos2d::CCArray *&array1);
    
private:
    string m_sFilePath;
    bool isXMLFileExist();
    void groundNodeToArray(XMLElement *ground,CCArray *&array);
	void eleNodeToArray(XMLElement *ele,CCArray *&array1);
};

#endif /* defined(__Runner__FDTinyXML2__) */
