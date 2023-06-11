#pragma once
#include <string>
#include <vector>

/**
 * @class Bonus
 * This class is responsible for Player bonuses
 */
class Bonus
{
public:
    Bonus(const char* pName);

    void setProbability(std::vector<int> pProbability);

    /**
     * This method checks whether the number is one of the probability numbers
     * and therefore the bonus should be activated.
     * @param number number of interest
     * @return true -> in probability, false -> not in probability
     */
    bool inProbability(int number);

    std::string getName();

private:
    std::vector<int> mProbability;
    std::string mName;
};
