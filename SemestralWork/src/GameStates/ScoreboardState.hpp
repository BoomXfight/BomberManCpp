#pragma once
#include "../GameObjects/GameObject.hpp"
#include "MenuState.hpp"

/**
 * @struct PlayerScore
 * This struct creates a simple way to represent player's names and their scores
 */
struct PlayerScore
{
    std::string name;
    int score;
};

/**
 * This function implements a comparator of 2 PlayerScore objects
 * @param[in] p1
 * @param[in] p2
 * @return true, false
 */
bool comparePlayers(const PlayerScore& p1, const PlayerScore& p2);

/**
 * This function loads the the Player's names and scores into the vector
 * @param[in] pFilename file to load from
 * @param[in,out] pPlayers vector to store to
 */
void loadPlayerScores(const std::string& pFilename, std::vector<PlayerScore>& pPlayers);

/**
 * This function updates the Player's stats file based on the vector
 * @param[in] pFilename
 * @param[in] pPlayers
 */
void modifyPlayerScores(const std::string& pFilename, const std::vector<PlayerScore>& pPlayers);

/**
 * @class ScoreboardState
 * This class implements the ScoreboardState
 */
class ScoreboardState : public MenuState
{
public:
    /**
     * This method is responsible for drawing the top 5 players to the screen
     */
    void render() override;

    /**
     * This method initializes the ScoreboardState from an xml file
     * @return true -> success, false -> failed to parse a gameState file
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of ScoreboardState
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    static void scoreboardToMainMenu();
    static void exit();
    static const std::string mMenuID;
    std::vector<PlayerScore> mPlayers;
};
