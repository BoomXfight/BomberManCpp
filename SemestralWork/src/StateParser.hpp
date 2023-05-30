#pragma once
#include "GameObjects/GameObject.hpp"
#include "tinyxml.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include <iostream>
#include <vector>

class StateParser
{
public:
    bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects,
                    std::vector<std::string> *pTextureIDs);

private:
    void parseObjects(xmlNodePtr objectRoot, std::vector<GameObject *> *pObjects);
    void parseTextures(xmlNodePtr textureRoot, std::vector<std::string> *pTextureIDs);
};
