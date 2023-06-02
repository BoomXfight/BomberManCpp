#include "Level.hpp"
#include "tinyxml.h"
#include "libxml/parser.h"
#include "libxml/tree.h"

class LevelParser
{
public:
    Level* parseLevel(const char* pLevelFile);

private:
    void parseTileSets(xmlNodePtr pTileSetRoot, std::vector<TileSet>* pTileSets);
    void parseTileLayer(xmlNodePtr pTileElement,std::vector<Layer*>* pLayers, const std::vector<TileSet>* pTileSets);
    void parseObjectLayer(xmlNodePtr pObjectElement, std::vector<Layer*>* pLayers);
    void parseTextures(xmlNodePtr pTextureRoot);

    int mTileSize;
    int mWidth;
    int mHeight;
};
