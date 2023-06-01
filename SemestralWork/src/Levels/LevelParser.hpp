#include "Level.hpp"
#include "tinyxml.h"
#include "libxml/parser.h"
#include "libxml/tree.h"

class LevelParser
{
public:
    Level* parseLevel(const char* levelFile);

private:
    void parseTileSets(xmlNodePtr pTileSetRoot, std::vector<Tileset>* pTileSets);
    void parseTileLayer(xmlNodePtr pTileElement,std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTileSets);
    void parseObjectLayer(xmlNodePtr pObjectElement, std::vector<Layer*> *pLayers);
    void parseTextures(xmlNodePtr pTextureRoot);

    int m_tileSize;
    int m_width;
    int m_height;
};