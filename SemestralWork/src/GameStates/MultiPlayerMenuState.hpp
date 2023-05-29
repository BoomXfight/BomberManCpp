#include "GameState.hpp"
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class MultiPlayerMenuState : public MenuState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const {return s_menuID;};

private:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    static void menuToQuit();
    static void MpMenuToMainMenu();
    static void MpMenuToMpPlay();

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};