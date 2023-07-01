#include "StateParser.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"

bool StateParser::parseState(const char* pStateFile, const std::string& pStateID,
                             std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs)
{
    xmlDocPtr doc = xmlReadFile(pStateFile, nullptr, 0);
    try
    {
        if (doc == nullptr)
            throw std::runtime_error("Failed to load the GameState xml file.");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    xmlNodePtr rootNode = xmlDocGetRootElement(doc);

    xmlNodePtr stateRoot = nullptr;
    for (xmlNodePtr node = rootNode->children; node != nullptr; node = node->next)
    {
        if (xmlStrcmp(node->name, (const xmlChar*)pStateID.c_str()) == 0)
        {
            stateRoot = node;
            break;
        }
    }

    xmlNodePtr textureRoot = nullptr;
    for (xmlNodePtr node = stateRoot->children; node != nullptr; node = node->next)
    {
        if (xmlStrcmp(node->name, (const xmlChar*)"TEXTURES") == 0)
        {
            textureRoot = node;
            break;
        }
    }

    //we parse the textures
    parseTextures(textureRoot, pTextureIDs);

    xmlNodePtr objectRoot = nullptr;
    for (xmlNodePtr node = stateRoot->children; node != nullptr; node = node->next)
    {
        if (xmlStrcmp(node->name, (const xmlChar*)"OBJECTS") == 0)
        {
            objectRoot = node;
            break;
        }
    }

    //we parse the objects
    parseObjects(objectRoot, pObjects);
    xmlFreeDoc(doc);
    return true;
}

void StateParser::parseObjects(xmlNodePtr pObjectRoot, std::vector<GameObject*>* pObjects)
{
    for (xmlNodePtr node = pObjectRoot->children; node != nullptr; node = node->next)
    {
        if (node->type == XML_ELEMENT_NODE)
        {
            int x, y, width, height, numFrames = 0, callbackID = 0;
            std::string textureID, type;

            xmlChar* typeAttr = xmlGetProp(node, (const xmlChar*)"type");
            xmlChar* xAttr = xmlGetProp(node, (const xmlChar*)"x");
            xmlChar* yAttr = xmlGetProp(node, (const xmlChar*)"y");
            xmlChar* widthAttr = xmlGetProp(node, (const xmlChar*)"width");
            xmlChar* heightAttr = xmlGetProp(node, (const xmlChar*)"height");
            xmlChar* numFramesAttr = xmlGetProp(node, (const xmlChar*)"numFrames");
            xmlChar* callbackIDAttr = xmlGetProp(node, (const xmlChar*)"callbackID");
            xmlChar* textureIDAttr = xmlGetProp(node, (const xmlChar*)"textureID");

            if(callbackIDAttr)
                callbackID = std::stoi((const char*)callbackIDAttr);

            if (xAttr && yAttr && widthAttr && heightAttr && textureIDAttr)
            {
                x = std::stoi((const char*)xAttr);
                y = std::stoi((const char*)yAttr);
                width = std::stoi((const char*)widthAttr);
                height = std::stoi((const char*)heightAttr);
                textureID = (const char*)textureIDAttr;
                type = (const char*)typeAttr;

                GameObject* pGameObject = TheGameObjectFactory::Instance()->create(type);
                pGameObject->load(new LoaderParams(x, y, width, height, numFrames, textureID, callbackID));
                pObjects->push_back(pGameObject);
            }

            xmlFree(xAttr);
            xmlFree(yAttr);
            xmlFree(widthAttr);
            xmlFree(heightAttr);
            xmlFree(numFramesAttr);
            xmlFree(callbackIDAttr);
            xmlFree(textureIDAttr);
        }
    }
}

void StateParser::parseTextures(xmlNodePtr pTextureRoot, std::vector<std::string>* pTextureIDs)
{
    for (xmlNodePtr node = pTextureRoot->children; node != nullptr; node = node->next)
    {
        if (node->type == XML_ELEMENT_NODE)
        {
            xmlChar* filenameAttr = xmlGetProp(node, (const xmlChar*)"filename");
            xmlChar* idAttr = xmlGetProp(node, (const xmlChar*)"ID");
            if (filenameAttr && idAttr)
            {
                std::string filename((const char*)filenameAttr);
                std::string id((const char*)idAttr);
                pTextureIDs->push_back(id); // push into list
                TheTextureManager::Instance()->load(filename, id, TheGame::Instance()->getRenderer());
            }
            xmlFree(filenameAttr);
            xmlFree(idAttr);
        }
    }
}
