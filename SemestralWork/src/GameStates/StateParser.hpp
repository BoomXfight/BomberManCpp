#pragma once
#include "../GameObjects/GameObject.hpp"
#include "tinyxml.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include <iostream>
#include <vector>

class StateParser
{
public:
    bool parseState(const char* pStateFile, const std::string& pStateID, std::vector<GameObject*>* pObjects,
                    std::vector<std::string>* pTextureIDs);

private:
    void parseObjects(xmlNodePtr pObjectRoot, std::vector<GameObject*>* pObjects);
    void parseTextures(xmlNodePtr pTextureRoot, std::vector<std::string>* pTextureIDs);
};
