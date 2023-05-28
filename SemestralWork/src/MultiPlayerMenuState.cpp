#include "MultiPlayerMenuState.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "StaticObject.hpp"
#include "TextSquare.hpp"
#include "MenuButton.hpp"
#include "MainMenuState.hpp"
#include "MultiPlayerPlayState.hpp"
#include <iostream>

void MultiPlayerMenuState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

void MultiPlayerMenuState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool MultiPlayerMenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../Assets/MultiPlayerHeading.png", "MultiPlayer", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Exit.png", "Exit", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Back.png", "Back", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Bomberman3.png", "BomberMan", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/BomberWoman.png", "BomberWoman", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Player1.png", "Player1", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Player2.png", "Player2", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/PlayButton.png", "Play", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/InputSquare.png", "Input", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* multiPlayer = new StaticObject(new LoaderParams(150, 10, 660, 166, "MultiPlayer"));
    GameObject* bomberMan = new StaticObject(new LoaderParams(30, 220, 271, 300, "BomberMan"));
    GameObject* bomberWoman = new StaticObject(new LoaderParams(720, 220, 197, 300, "BomberWoman"));
    GameObject* player1 = new StaticObject(new LoaderParams(320, 190, 160, 30, "Player1"));
    GameObject* player2 = new StaticObject(new LoaderParams(320, 280, 160, 30, "Player2"));
    GameObject* exit = new MenuButton(new LoaderParams(840, 40, 90, 50, "Exit"), menuToQuit);
    GameObject* back = new MenuButton(new LoaderParams(30, 40, 90, 50, "Back"), MpMenuToMainMenu);
    GameObject* play = new MenuButton(new LoaderParams(380, 360, 200, 160, "Play"), MpMenuToMpPlay);
    GameObject* p1 = new TextSquare(new LoaderParams(490, 190, 200, 60, "Input"));
    GameObject* p2 = new TextSquare(new LoaderParams(490, 280, 200, 60, "Input"));

    m_gameObjects.push_back(p1);
    m_gameObjects.push_back(p2);
    m_gameObjects.push_back(multiPlayer);
    m_gameObjects.push_back(exit);
    m_gameObjects.push_back(back);
    m_gameObjects.push_back(bomberMan);
    m_gameObjects.push_back(bomberWoman);
    m_gameObjects.push_back(player1);
    m_gameObjects.push_back(player2);
    m_gameObjects.push_back(play);

    std::cout << "entering MultiPlayerMenu state\n";
    return true;
}

bool MultiPlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(m_gameObjects[0])) {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set" << std::endl;
    }

    if(TextSquare* b = dynamic_cast<TextSquare*>(m_gameObjects[1])) {
        TheGame::Instance()->setP2(b->getText());
        std::cout << "P1 set" << std::endl;
    }

    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("MultiPlayer");
    TheTextureManager::Instance()->clearFromTextureMap("Exit");
    TheTextureManager::Instance()->clearFromTextureMap("Back");
    TheTextureManager::Instance()->clearFromTextureMap("Input");
    TheTextureManager::Instance()->clearFromTextureMap("BomberMan");
    TheTextureManager::Instance()->clearFromTextureMap("BomberWoman");
    TheTextureManager::Instance()->clearFromTextureMap("Player1");
    TheTextureManager::Instance()->clearFromTextureMap("Player2");
    TheTextureManager::Instance()->clearFromTextureMap("Play");
    std::cout << "exiting MultiPlayerMenuState\n";
    return true;
}

void MultiPlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

void MultiPlayerMenuState::MpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void MultiPlayerMenuState::MpMenuToMpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Player1 : " << TheGame::Instance()->getP1() << std::endl;
    else
        std::cout << "Player1 : guest" << std::endl;

    if(TheGame::Instance()->P2Ready())
        std::cout << "Player2 : " << TheGame::Instance()->getP2() << std::endl;
    else
        std::cout << "Player2 : guest" << std::endl;
}