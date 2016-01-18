//
// Created by tdgunes on 3/23/15.
//

// from:
// http://stackoverflow.com/questions/12971499/how-to-get-the-file-separator-symbol-in-standard-c-c-or
#if defined(WIN32) || defined(_WIN32)
    #define PATH_SEPARATOR "/"
    #define ENTITIES_DIR ".\\assets\\entities\\"
#else
    #define PATH_SEPARATOR "/"
    #define ENTITIES_DIR "./assets/entities/"
#endif

#define OBJ_EXTENSION ".obj"


#ifndef _SPYE_CONSTANTS_H_
#define _SPYE_CONSTANTS_H_

#include <string>


#endif //_SPYE_CONSTANTS_H_
