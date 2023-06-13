#pragma once
#include <string>
#include <vector>

/**
 * @class GameState
 * This is a base class for every GameState in the game
 */
class GameState
{
public:
    GameState();
    virtual ~GameState();

    /**
     * This class will update the GameState
     */
    virtual void update() = 0;

    /**
     * This class will render the GameState
     */
    virtual void render() = 0;

    /**
     * This class will load up the GameState upon entering it
     * @return
     */
    virtual bool onEnter() = 0;

    /**
     * This class will clean after the GameState at the end of it
     * @return
     */
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;

protected:
    std::vector<std::string> mTextureIDList;
};
