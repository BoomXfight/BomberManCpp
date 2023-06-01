#include "LevelParser.hpp"
#include "Singletons/Game.hpp"
#include "Singletons/TextureManager.hpp"
#include "Singletons/GameObjectFactory.hpp"
#include "TileLayer.hpp"
#include "ObjectLayer.hpp"
#include "LoaderParams.hpp"

Level* LevelParser::parseLevel(const char *levelFile)
{
    // create a TinyXML document and load the map XML
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // create the level object
    Level* pLevel = new Level();

    // get the root node
    TiXmlElement* pRoot = levelDocument.RootElement();

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    // parse the tilese
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << e->Value() << std::endl;
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    // parse any object layers
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << e->Value() << std::endl;
        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if (e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayer(e, pLevel->getLayers());
            }
            else if (e->FirstChildElement()->Value() == std::string("data"))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
            }
        }
    }

    // we must parse the textures needed for this level, which have been
    // added to properties
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << e->Value() << std::endl;
        if(e->Value() == std::string("properties"))
        {
            parseTextures(e->FirstChildElement());
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    // first add the tileset to texture manager
    TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"),
                                        pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width",&tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height",&tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers,
                                 const std::vector<Tileset>* pTilesets)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    // tile data
    std::vector<std::vector<int>> data;
    std::string decodeIDs;

    TiXmlElement* pDataNode;
    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    } // Data node found

    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        decodeIDs = text->Value();
    }

    std::vector<int> gids;
    for(int i = 0; i < decodeIDs.size(); i++)
    {
        if(isdigit(decodeIDs[i]))
        {
            gids.push_back(decodeIDs[i] - 48);
        }
    }
    std::cout << std::endl;


    for(int i = 0; i < gids.size(); i++)
        std::cout << gids[i] << " ";
    std::cout << std::endl;

    std::vector<int> layerRow(m_width);

    for(int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for(int rows = 0; rows < m_height; rows++)
    {
        for (int cols = 0; cols < m_width; cols++) {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }
    std::cout << "\n\n" << std::endl;

    for(int rows = 0; rows < m_height; rows++)
    {
        for(int cols = 0; cols < m_width; cols++)
        {
            std::cout << data[rows][cols];
        }
        std::cout << std::endl;
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
    TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"),
                                        TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers)
{
// create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    std::cout << pObjectElement->FirstChildElement()->Value();
    for(TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << e->Value();
        if(e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackID, animSpeed;
            std::string textureID;
            // get the initial node values type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);
            GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
            // get the property values
            for(TiXmlElement* properties = e->FirstChildElement();properties != NULL; properties = properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                                property->Attribute("value", &numFrames);

                            else if(property->Attribute("name") == std::string("textureHeight"))
                                property->Attribute("value", &height);

                            else if(property->Attribute("name") == std::string("textureID"))
                                textureID = property->Attribute("value");

                            else if(property->Attribute("name") == std::string("textureWidth"))
                                property->Attribute("value", &width);

                            else if(property->Attribute("name") == std::string("callbackID"))
                                property->Attribute("value", &callbackID);

                            else if(e->Attribute("name") == std::string("animSpeed"))
                                property->Attribute("value", &animSpeed);
                        }
                    }
                }
            }
            pGameObject->load(new LoaderParams(x, y, width, height, numFrames, textureID, callbackID));
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    pLayers->push_back(pObjectLayer);
}
