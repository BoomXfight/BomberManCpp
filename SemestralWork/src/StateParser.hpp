#pragma once
#include "GameObject.hpp"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include <iostream>
#include <vector>

/**
 * @class StateParser
 * This class is responsible for loading GameStates from the xml state file.
 */
class StateParser
{
public:
    /**
     * This method parses the xml file and loads the GameState from it.
     * @param pStateFile file to load from.
     * @param pStateID unique state identifier.
     * @param pObjects place to store the GameObjects.
     * @param pTextureIDs place to store TextureIDs.
     * @return true -> success , false -> failed to initialize the file.
     * @throw std::runtime_error when failed to load the file.
     */
    bool parseState(const char* pStateFile, const std::string& pStateID, std::vector<GameObject*>* pObjects,
                    std::vector<std::string>* pTextureIDs);

private:
    /**
     * This method parses the object part of the GameState xml file.
     * @param pObjectRoot root position to start parsing from.
     * @param pObjects place to store the objects.
     */
    void parseObjects(xmlNodePtr pObjectRoot, std::vector<GameObject*>* pObjects);

    /**
     * his method parses the texture part of the GameState xml file
     * @param pTextureRoot root position to start parsing from.
     * @param pTextureIDs place to store the TextureIDs.
     */
    void parseTextures(xmlNodePtr pTextureRoot, std::vector<std::string>* pTextureIDs);
};
