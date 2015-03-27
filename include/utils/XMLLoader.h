//
// Created by Taha Doğan Güneş on 26/03/15.
//

#ifndef _SPYE_XMLLOADER_H_
#define _SPYE_XMLLOADER_H_

#include <string>

#include "utils/rapidxml.hpp"
#include "utils/rapidxml_utils.hpp"

class XMLLoader {


public:
    rapidxml::xml_document<> *getDocument(const char *path) {
        try {
            rapidxml::file<> file(path);
            rapidxml::xml_document<> *document = new rapidxml::xml_document<>();
            document->parse<0>(file.data());
            return document;
        }
        catch (const std::runtime_error &error) {
            printf("[XMLLoader] With error: %s\n", error.what());
            return NULL;
        }
    }

};

#endif //_SPYE_XMLLOADER_H_
