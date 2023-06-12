#pragma once
#include "../Levels/Level.hpp"
#include "../Levels/ObjectLayer.hpp"
#include "../GameObjects/GameObject.hpp"
#include "ScoreboardState.hpp"
#include <vector>

/**
 * @class SinglePlayerPlayState
 * This class is responsible for the SinglePlayerPlayState. A state where 1 player fights against computer enemies.
 */
class SinglePlayerPlayState : public GameState
{
public:
    /**
     * This method updates the current level as well as checks for a game pause.
     */
    void update() override;

    /**
     * This method renders the current level.
     */
    void render() override;

    /**
     * This method initializes the current level from the file.
     * @return true
     * @throw std::runtime_error if failed to load the level file.
     */
    bool onEnter() override;

    /**
     * This method cleans up after the current game state.
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    /**
     * This method gets the necessary Player information and handles the score and enemy count.
     */
    void updatePlayer();

    /**
     * This method renders the necessary Level information to the screen.
     */
    void renderGameInformation() const;

    /**
     * This method updates of the Player score at the end of the Level.
     * @param pScores
     */
    void updatePlayersScore(std::vector<PlayerScore>& pScores);

    int mLives;
    int mSpeed;
    int mRadius;
    int mNoOfEnemies;
    int mScore;
    bool mBombTime;
    bool mImmortal;

    static const std::string mStateID;
    ObjectLayer* mObjectLayer;
    std::vector<GameObject*> mGameObjects;
    Level* mLevel;
};
