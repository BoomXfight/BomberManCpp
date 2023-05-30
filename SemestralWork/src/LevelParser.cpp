#include "LevelParser.hpp"
#include "Singletons/Game.hpp"
#include "Singletons/TextureManager.hpp"
#include "TileLayer.hpp"

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
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    // parse any object layers
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
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