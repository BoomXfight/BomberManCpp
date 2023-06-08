#include "Level.hpp"
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
    void parseBonuses(xmlNodePtr pBonusRoot, std::vector<Bonus*>* pBonuses);

    int mTileSize;
    int mWidth;
    int mHeight;
};
