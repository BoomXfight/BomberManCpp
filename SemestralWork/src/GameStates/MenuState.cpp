#include "../GameObjects/MenuButton.hpp"
#include "MenuState.hpp"

MenuState::MenuState() = default;

void MenuState::update()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

void MenuState::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

void MenuState::setCallbacks(const std::vector<Callback> &pCallbacks)
{
    for (int i = 0; i < mGameObjects.size(); i++) {
        // MenuButton requires callback function
        if (dynamic_cast<MenuButton *>(mGameObjects[i])) {
            MenuButton *pButton = dynamic_cast<MenuButton *>(mGameObjects[i]);
            pButton->setCallback(pCallbacks[pButton->getCallbackID()]);
        }
    }
}
