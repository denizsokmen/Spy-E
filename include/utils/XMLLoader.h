#ifndef SPYE_XMLLOADER_H
#define SPYE_XMLLOADER_H

#include <string>
#include <fstream>
#include "utils/rapidxml.hpp"
#include "rapidxml_utils.hpp"

class XMLLoader {

protected:
    rapidxml::file<> *file;
    rapidxml::xml_document<> *document = new rapidxml::xml_document<>();

public:

    rapidxml::xml_document<> *getDocument(const char *path) {
        try {
            file = new rapidxml::file<>(path);
            document->parse<0>(file->data());
            return document;
        }
        catch (const std::runtime_error &error) {
            printf("[XMLLoader] With error: %s\n", error.what());
            return NULL;
        }
        return NULL;
    }

};

#endif //SPYE_XMLLOADER_H
