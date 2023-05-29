#pragma once
#include "GameState.hpp"
#include <vector>

class MenuState : public GameState
{
public:
    MenuState();

protected:
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};

