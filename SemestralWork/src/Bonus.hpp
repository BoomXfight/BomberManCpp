#pragma once
#include <string>
#include <vector>

class Bonus
{
public:
    Bonus(const char* pName);
    ~Bonus();
    void setProbability(std::vector<int> v);
    bool inProbability(int number);
    std::string getName();

private:
    std::vector<int> mProbability;
    std::string mName;
};