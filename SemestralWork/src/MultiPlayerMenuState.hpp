#include "GameState.hpp"
#include "GameObject.hpp"
#include <vector>

class MultiPlayerMenuState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const {return s_menuID;};

private:
    static void menuToQuit();
    static void SpMenuToMainMenu();

    std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};