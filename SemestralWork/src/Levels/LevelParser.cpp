#include "LevelParser.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/GameObjectFactory.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "TileLayer.hpp"
#include "ObjectLayer.hpp"
#include "../LoaderParams.hpp"

/**
 * This method is used to parse a level from an xml file : map, as well as objects
 * and creates a level from the file
 * @param[in] levelFile
 * @return Level* -> created level
 */
Level* LevelParser::parseLevel(const char* pLevelFile)
{
    xmlDocPtr levelDocument = xmlParseFile(pLevelFile);

    Level* level = new Level();

    // get the root node
    xmlNodePtr root = xmlDocGetRootElement(levelDocument);

    xmlChar* tileSizeAttr = xmlGetProp(root, (const xmlChar*)"tilewidth");
    xmlChar* widthAttr = xmlGetProp(root, (const xmlChar*)"width");
    xmlChar* heightAttr = xmlGetProp(root, (const xmlChar*)"height");

    mTileSize = atoi((const char*)tileSizeAttr);
    mWidth = atoi((const char*)widthAttr);
    mHeight = atoi((const char*)heightAttr);

    xmlFree(tileSizeAttr);
    xmlFree(widthAttr);
    xmlFree(heightAttr);

    // parse the tileSet
    for (xmlNodePtr e = root->children; e != nullptr; e = e->next)
    {
        if (xmlStrcmp(e->name, (const xmlChar*)"tileset") == 0)
            parseTileSets(e, level->getTileSets());
    }

    // parse object layers and tile layers
    for (xmlNodePtr e = root->children; e != nullptr; e = e->next)
    {
        if (xmlStrcmp(e->name, (const xmlChar*)"objectgroup") == 0 || xmlStrcmp(e->name, (const xmlChar*)"layer") == 0)
        {
            xmlNodePtr firstChild = e->children->next;
            if (firstChild != nullptr)
            {
                if (xmlStrcmp(firstChild->name, (const xmlChar*)"object") == 0)
                    parseObjectLayer(e, level->getLayers());

                else if (xmlStrcmp(firstChild->name, (const xmlChar*)"data") == 0)
                    parseTileLayer(e, level->getLayers(), level->getTileSets());
            }
        }
    }

    // parse textures
    for (xmlNodePtr e = root->children; e != nullptr; e = e->next)
    {
        if (xmlStrcmp(e->name, (const xmlChar*)"objectProperties") == 0)
        {
            xmlNodePtr firstChild = e->children;
            if (firstChild != nullptr)
                parseTextures(firstChild);
        }
    }

    xmlFreeDoc(levelDocument);
    return level;
}

/**
 * This method parses a tileSet information required for map rendering
 * @param[in] pTileSetRoot
 * @param[in,out] pTileSets
 */
void LevelParser::parseTileSets(xmlNodePtr pTileSetRoot, std::vector<TileSet>* pTileSets)
{
    // add the map sheet into the texture manager
    xmlNode* firstChild = pTileSetRoot->children->next;
    xmlChar* source = xmlGetProp(firstChild, (const xmlChar*)"source");
    xmlChar* name = xmlGetProp(pTileSetRoot, (const xmlChar*)"name");
    TheTextureManager::Instance()->load((const char*)source,(const char*)name, TheGame::Instance()->getRenderer());

    xmlFree(source);

    // create a tileSet object
    TileSet tileSet;
    if (firstChild != nullptr)
    {
        xmlChar* widthAttr = xmlGetProp(firstChild, (const xmlChar*)"width");
        xmlChar* heightAttr = xmlGetProp(firstChild, (const xmlChar*)"height");

        tileSet.mWidth = atoi((const char*)widthAttr);
        tileSet.mHeight = atoi((const char*)heightAttr);

        xmlFree(widthAttr);
        xmlFree(heightAttr);
    }

    xmlChar* firstGridAttr = xmlGetProp(pTileSetRoot, (const xmlChar*)"firstgid");
    xmlChar* tileWidthAttr = xmlGetProp(pTileSetRoot, (const xmlChar*)"tilewidth");
    xmlChar* tileHeightAttr = xmlGetProp(pTileSetRoot, (const xmlChar*)"tileheight");
    xmlChar* spacingAttr = xmlGetProp(pTileSetRoot, (const xmlChar*)"spacing");
    xmlChar* marginAttr = xmlGetProp(pTileSetRoot, (const xmlChar*)"margin");
    xmlChar* columnsAttr = xmlGetProp(pTileSetRoot, (const xmlChar*)"columns");

    tileSet.mFirstGridID = atoi((const char*)firstGridAttr);
    tileSet.mTileWidth = atoi((const char*)tileWidthAttr);
    tileSet.mTileHeight = atoi((const char*)tileHeightAttr);
    tileSet.mSpacing = atoi((const char*)spacingAttr);
    tileSet.mMargin = atoi((const char*)marginAttr);
    tileSet.mNumColumns = atoi((const char*)columnsAttr);
    tileSet.mName = (const char*) name;

    xmlFree(firstGridAttr);
    xmlFree(tileWidthAttr);
    xmlFree(tileHeightAttr);
    xmlFree(spacingAttr);
    xmlFree(marginAttr);
    xmlFree(columnsAttr);
    xmlFree(name);

    pTileSets->push_back(tileSet);
}

/**
 * This method parses the map matrix from an xml file and stores the information in a 2D map array
 * @param[in] pTileElement
 * @param[in,out] pLayers
 * @param[in,out] pTileSets
 */
void LevelParser::parseTileLayer(xmlNodePtr pTileElement, std::vector<Layer*> *pLayers,
                                 const std::vector<TileSet>* pTileSets)
{
    TileLayer* pTileLayer = new TileLayer(mTileSize, *pTileSets);

    // Tile data
    std::vector<std::vector<int>> data; // 2D array for representing the map
    std::string decodeIDs;

    xmlNodePtr pDataNode = nullptr; // Find the data node
    for (xmlNodePtr e = pTileElement->children; e != nullptr; e = e->next)
    {
        if (xmlStrcmp(e->name, (const xmlChar*)"data") == 0)
        {
            pDataNode = e;
            break;
        }
    }

    // Get the data of the map matrix
    for (xmlNodePtr e = pDataNode->children; e != nullptr; e = e->next)
    {
        xmlChar* textContent = xmlNodeGetContent(e);
        decodeIDs = (const char*)textContent;
        xmlFree(textContent);
        break;
    }

    // Transfer the data from the string to vector of integers
    std::vector<int> ids;
    for (size_t i = 0; i < decodeIDs.size(); i++)
    {
        if (isdigit(decodeIDs[i]))
            ids.push_back(decodeIDs[i] - '0');
    }

    // Finally create a 2D map matrix
    std::vector<int> layerRow(mWidth);
    for (int j = 0; j < mHeight; j++)
        data.push_back(layerRow);

    for (int rows = 0; rows < mHeight; rows++)
        for (int cols = 0; cols < mWidth; cols++)
            data[rows][cols] = ids[rows * mWidth + cols];

    pTileLayer->setTileIDs(data);
    TheCollisionManager::Instance()->setTileLayer(pTileLayer);
    pLayers->push_back(pTileLayer);
}

/**
 * This method finds and creates gameObjects from an xml folder
 * @param[in] pObjectElement
 * @param[in,out] pLayers
 */
void LevelParser::parseObjectLayer(xmlNodePtr pObjectElement, std::vector<Layer*> *pLayers)
{
    ObjectLayer* pObjectLayer = new ObjectLayer();

    for(xmlNodePtr e = pObjectElement->children; e != nullptr; e = e->next)
    {
        if(xmlStrcmp(e->name, (const xmlChar*)"object") == 0)
        {
            int x, y, width, height, numFrames, callbackID;
            std::string textureID;

            xmlChar* xAttr = xmlGetProp(e, (const xmlChar*)"x");
            xmlChar* yAttr = xmlGetProp(e, (const xmlChar*)"y");
            x = atoi((const char*)xAttr);
            y = atoi((const char*)yAttr);

            xmlFree(xAttr);
            xmlFree(yAttr);

            //Create an object found in the file
            xmlChar* typeAttr = xmlGetProp(e, (const xmlChar*)"type");
            GameObject* pGameObject = TheGameObjectFactory::Instance()->create((const char*)typeAttr);
            xmlFree(typeAttr);

            for (xmlNodePtr properties = e->children->next; properties != nullptr; properties = properties->next)
            {
                if (xmlStrcmp(properties->name, (const xmlChar*)"properties") == 0)
                {
                    for (xmlNodePtr property = properties->children; property != nullptr; property = property->next)
                    {
                        if (xmlStrcmp(property->name, (const xmlChar*)"property") == 0)
                        {
                            xmlChar* nameAttr = xmlGetProp(property, (const xmlChar*)"name");
                            xmlChar* valueAttr = xmlGetProp(property, (const xmlChar*)"value");

                            std::string propertyName = (const char*)nameAttr;
                            if (propertyName == "numFrames")
                                numFrames = atoi((const char*)valueAttr);
                            else if (propertyName == "textureHeight")
                                height = atoi((const char*)valueAttr);
                            else if (propertyName == "textureWidth")
                                width = atoi((const char*)valueAttr);
                            else if (propertyName == "textureID")
                                textureID = (const char*)valueAttr;
                            else if (propertyName == "callbackID")
                                callbackID = atoi((const char*)valueAttr);

                            xmlFree(nameAttr);
                            xmlFree(valueAttr);
                        }
                    }
                }
            }

            pGameObject->load(new LoaderParams(x, y, width, height, numFrames, textureID, callbackID));
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    TheCollisionManager::Instance()->setObjectLayer(pObjectLayer);
    pLayers->push_back(pObjectLayer);
}

/**
 * This method loads a required textures by gameObjects to TheTextureManager to be used in the game
 * @param pTextureRoot
 */
void LevelParser::parseTextures(xmlNodePtr pTextureRoot)
{
    xmlChar* valueAttr = nullptr;
    xmlChar* nameAttr = nullptr;

    for (xmlNodePtr e = pTextureRoot; e != nullptr; e = e->next)
    {
        if(xmlStrcmp(e->name, (const xmlChar*)"property") == 0)
        {
            valueAttr = xmlGetProp(e, (const xmlChar*)"value");
            nameAttr = xmlGetProp(e, (const xmlChar*)"name");
            TheTextureManager::Instance()->load((const char*)valueAttr, (const char*)nameAttr,
                                                TheGame::Instance()->getRenderer());
        }
    }

    xmlFree(valueAttr);
    xmlFree(nameAttr);
}
