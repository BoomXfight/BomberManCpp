#include "Bonus.hpp"
#include <algorithm>

Bonus::Bonus(const char* pName) : mName(pName)
{}

void Bonus::setProbability(std::vector<int> v)
{
    mProbability = v;
}

std::string Bonus::getName()
{
    return mName;
};

bool Bonus::inProbability(int number)
{
    auto it = std::find(mProbability.begin(), mProbability.end(), number);
    return (it != mProbability.end());
}
