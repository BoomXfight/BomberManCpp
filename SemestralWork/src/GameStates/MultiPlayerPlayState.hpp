#pragma once
#include "../Levels/Level.hpp"
#include "ScoreboardState.hpp"
#include "GameState.hpp"

/**
 * @class MultiPlayerPlayState
 * This class implements the MultiPlayerPlayState, a state where 2 players compete against each other on the same keyboard.
 */
class MultiPlayerPlayState : public GameState
{
public:
    /**
     * This method updates the current level as well as checks for a game pause
     */
    void update() override;

    /**
     * This method renders the current level
     */
    void render() override;

    /**
     * This method initializes the current level from the file
     * @return true
     */
    bool onEnter() override;

    /**
     * This method cleans up after the current game state and saves the result scores
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    /**
     * This method gets the necessary player information
     */
    void handlePlayers();

    /**
     * This method handles the rendering of player1 information to the screen
     */
    void handlePlayer1Information() const;

    /**
     * This method handles the rendering of player2 information to the screen
     */
    void handlePlayer2Information() const;

    /**
     * This method updates the player scores at the end of the level
     * @param[in,out] pScores
     */
    void updatePlayersScore(std::vector<PlayerScore>& pScores);

    int mP1Score;
    int mP2Score;
    int mP1Lives;
    int mP2Lives;
    int mP1Speed;
    int mP2Speed;
    int mP1Radius;
    int mP2Radius;
    bool mP1Immortal;
    bool mP2Immortal;
    bool mP1BombTime;
    bool mP2BombTime;
    bool mP1Dmg;
    bool mP2Dmg;

    Uint32 mDmg1Timer;
    Uint32 mDmg2Timer;
    Uint32 mNow;

    static const std::string mStateID;
    Level* mLevel;
};
