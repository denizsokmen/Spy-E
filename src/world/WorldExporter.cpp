
#include "world/WorldExporter.h"
#include "utils/tinyxml2.h"
#include <vector>
#include <string>
#include <stdio.h>
#include "world/World.h"
#include "world/Entity.h"



WorldExporter::WorldExporter() {
    this->rootNode = xmlDocument.NewElement("Map");
    xmlDocument.InsertFirstChild(rootNode);
}

bool WorldExporter::save(std::string mapName, std::string mapVersion, std::string path, World* world) {

    addTextElement("Name", mapName.c_str());
    addTextElement("Version", mapVersion.c_str());
    addTextElement("SkyBox", "N/A");


    saveEntities(world);

    std::string documentName = path+mapName+"-"+mapVersion+".xml";
    tinyxml2::XMLError errorResult = xmlDocument.SaveFile(documentName.c_str());
//    tinyxml2::XMLCheckResult(errorResult);


    if (errorResult == tinyxml2::XML_NO_ERROR) {
        printf("World saved to '%s' \n", documentName.c_str());
        return true;
    }
    printf("Unable to save world to '%s' with error %i \n", documentName.c_str(), errorResult);
    return false;
}

void WorldExporter::saveEntities(World *world) {
    tinyxml2::XMLElement *element = xmlDocument.NewElement("Entities");

    for (Entity *&entity : world->getEntities()) {
        tinyxml2::XMLElement *entityElement = saveEntity(entity);
        element->InsertEndChild(entityElement);
    }

    element->SetAttribute("count", (unsigned int) world->getEntityCount());
    rootNode->InsertEndChild(element);
}

tinyxml2::XMLElement *WorldExporter::saveEntity(Entity *&entity) {
    tinyxml2::XMLElement *entityElement = xmlDocument.NewElement("Entity");

    tinyxml2::XMLElement *nameElement = xmlDocument.NewElement("Name");
    tinyxml2::XMLElement *fileNameElement = xmlDocument.NewElement("FileName");

    tinyxml2::XMLElement *positionElement = xmlDocument.NewElement("Position");
    tinyxml2::XMLElement *xElement = xmlDocument.NewElement("X");
    tinyxml2::XMLElement *yElement = xmlDocument.NewElement("Y");
    tinyxml2::XMLElement *zElement = xmlDocument.NewElement("Z");


    xElement->SetText(1.0);
    yElement->SetText(1.0);
    zElement->SetText(1.0);

    positionElement->InsertEndChild(xElement);
    positionElement->InsertEndChild(yElement);
    positionElement->InsertEndChild(zElement);

    fileNameElement->SetText("../fileName.xml");
//    nameElement->SetText(entity->name.c_str());


    entityElement->InsertEndChild(nameElement);
    entityElement->InsertEndChild(fileNameElement);
    entityElement->InsertEndChild(positionElement);


    return entityElement;
}

void WorldExporter::addTextElement(const char* key , const char *value) {
    tinyxml2::XMLElement* element = xmlDocument.NewElement(key);
    element->SetText(value);
    rootNode->InsertEndChild(element);
}