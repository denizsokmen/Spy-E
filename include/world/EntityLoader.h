//
// Created by Enes Şenel on 13/03/15.
//

#ifndef _SPYE_ENTITYLOADER_H_
#define _SPYE_ENTITYLOADER_H_

#include <string>
#include "utils/tinyxml2.h"

class EntityLoader {

public:
    EntityLoader();
    ~EntityLoader();

private:
    tinyxml2::XMLDocument xmlDocument;
};


#endif //_SPYE_ENTITYLOADER_H_
