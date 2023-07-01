#include "Level.hpp"
#include "libxml/parser.h"
#include "libxml/tree.h"

/**
 * @class LevelParser
 * This class is responsible to parse a level xml file and load a level from it.
 */
class LevelParser
{
public:
    /**
     * This method is used to parse a level from an xml file : map, as well as objects.
     * It creates a level from the information gathered.
     * @param[in] levelFile file to parse.
     * @return Level* -> created level.
     */
    Level* parseLevel(const char* pLevelFile);

private:
    /**
     * This method parses a tileSet information required for map rendering
     * @param[in] pTileSetRoot root to parse from.
     * @param[in,out] pTileSets place to store TileSet.
     */
    void parseTileSets(xmlNodePtr pTileSetRoot, std::vector<TileSet>* pTileSets);

    /**
     * This method parses the map matrix from an xml file and stores the information in a 2D map array
     * @param[in] pTileElement starting position.
     * @param[in,out] pLayers place to store Layers.
     * @param[in,out] pTileSets place to store TileSets.
     */
    void parseTileLayer(xmlNodePtr pTileElement,std::vector<Layer*>* pLayers, const std::vector<TileSet>* pTileSets) const;

    /**
     * This method finds and creates gameObjects from an xml folder
     * @param[in] pObjectElement starting point.
     * @param[in,out] pLayers place to store ObjectLayer.
     */
    void parseObjectLayer(xmlNodePtr pObjectElement, std::vector<Layer*>* pLayers);

    /**
     * This method loads a required textures by gameObjects to TheTextureManager to be used in the game
     * @param pTextureRoot
     */
    void parseTextures(xmlNodePtr pTextureRoot);

    /**
     * This method parses the bonuses probability from the xml file
     * @param pBonusRoot starting point.
     * @param pBonuses place to store bonuses.
     */
    void parseBonuses(xmlNodePtr pBonusRoot, std::vector<Bonus*>* pBonuses);

    int mTileSize;
    int mWidth;
    int mHeight;
};
