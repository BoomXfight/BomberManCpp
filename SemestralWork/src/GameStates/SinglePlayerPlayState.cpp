#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "SinglePlayerPlayState.hpp"
#include "GameState.hpp"
#include "PauseMenuState.hpp"
#include <iostream>

void SinglePlayerPlayState::update()
{
    mLevel->update();
    mLevel->getLayers();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::Instance()->getStateMachine()->pushState(new PauseMenuState());
}

void SinglePlayerPlayState::render()
{
    mLevel->render();
}

bool SinglePlayerPlayState::onEnter()
{
    LevelParser levelParser;
    levelParser.parseLevel("../Assets/Maps/map1.tmx");
    std::cout << "Entering SinglePLayerPlayState" << std::endl;
    return true;
}

bool SinglePlayerPlayState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting SinglePlayerPlayState" << std::endl;
    return true;
}

const std::string SinglePlayerPlayState::mMenuID = "SINGLE_PLAYER_PLAY_STATE";
