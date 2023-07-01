#pragma once
#include "GameObject.hpp"
#include "GameStateMachine.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <memory>

/**
 * @class Game
 * This singleton class is responsible for creating a game, keeping it running and its communication with the main
 */
class Game
{
public:
    ~Game();

    /**
     * Static method that ensures only 1 existence of TheGame object
     * @return game object
     */
    static Game* Instance();

    /**
    * This method initializes the game.
    * @param[in] pTitle Game title.
    * @param[in] pX_WindowPos Window x coordinate.
    * @param[in] pY_WindowPos Window y coordinate.
    * @param[in] pWindowWidth
    * @param[in] pWindowHeight
    * @param[in] pFullscreen Fullscreen flag.
    * @return true -> Game initialization success, false -> Failed to initialize the game.
    * @throw std::runtime_error if the font fails to load.
    */
    bool init(const char* pTitle, int pX_WindowPos, int pY_WindowPos, int pWindowWidth, int pWindowHeight,
              bool pFullscreen);

    /**
    * This method renders the current game state to the screen.
    */
    void render();

    /**
    * This method updates the current game state.
    */
    void update();

    /**
    * This method handles the user interaction with the game.
    */
    void handleEvents();

    /**
    * This method cleans up after the game.
    */
    void clean();

    /**
     * This method stops the game.
     */
    void quit();

    void setP1(std::string s);

    void setP2(std::string s);

    bool P1Ready();

    bool P2Ready();

    bool isRunning();

    int getGameWidth() const;

    int getGameHeight() const;

    std::string getP1() const;

    std::string getP2() const;

    SDL_Renderer* getRenderer() const;

    GameStateMachine* getStateMachine() const;

    TTF_Font* getFont1() const;
    
    TTF_Font* getFont2() const;
    
    TTF_Font* getFont3() const;

private:
    Game();

    static Game* mInstance;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    TTF_Font* mFont1;
    TTF_Font* mFont2;
    TTF_Font* mFont3;

    int mGameWidth{};
    int mGameHeight{};
    bool mIsRunning{};

    std::string mPlayer1;
    std::string mPlayer2;

    GameStateMachine* mGameStateMachine{};
};

typedef Game TheGame;
