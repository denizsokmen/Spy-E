
#include "Exporter.h"
#include "tinyxml2.h"
#include <vector>
#include <stdio.h>

Exporter::Exporter() {
}

void Exporter::save() {
    tinyxml2::XMLDocument xmlDocument;
    tinyxml2::XMLNode* rootNode = xmlDocument.NewElement("Root");
    xmlDocument.InsertFirstChild(rootNode);
    tinyxml2::XMLElement* element = xmlDocument.NewElement("IntValue");
    element->SetText(10);
    rootNode->InsertEndChild(element);
    element = xmlDocument.NewElement("FloatValue");
    element->SetText(0.5f);
    rootNode->InsertEndChild(element);

    element = xmlDocument.NewElement("Date");
    element->SetAttribute("day", 26);
    element->SetAttribute("month", "April");
    element->SetAttribute("year", 2014);
    element->SetAttribute("dateFormat", "26/04/2014");

    rootNode->InsertEndChild(element);

    element = xmlDocument.NewElement("List");


    std::vector<int> vectorList;
    vectorList.push_back(1);
    vectorList.push_back(2);
    vectorList.push_back(3);
    vectorList.push_back(4);
    vectorList.push_back(5);

    for (const auto & item : vectorList)
    {
        tinyxml2::XMLElement * pListElement = xmlDocument.NewElement("Item");
        pListElement->SetText(item);

        element->InsertEndChild(pListElement);
    }

    element->SetAttribute("itemCount", (unsigned int)vectorList.size());
    rootNode->InsertEndChild(element);
    tinyxml2::XMLError errorResult = xmlDocument.SaveFile("SavedData.xml");
//    tinyxml2::XMLCheckResult(errorResult);


    printf("");
}