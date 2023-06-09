cmake_minimum_required(VERSION 3.25)
project(a)

set(CMAKE_CXX_STANDARD 17)

find_package(LibXml2 REQUIRED)

add_executable(a src/main.cpp src/Singletons/Game.cpp src/GameObjects/GameObject.cpp src/GameStates/GameState.cpp src/GameStates/GameStateMachine.cpp
        src/Singletons/InputHandler.cpp src/LoaderParams.cpp src/GameObjects/MenuButton.cpp src/GameStates/MainMenuState.cpp src/GameObjects/Player1.cpp src/GameObjects/Player2.cpp
        src/GameObjects/SDLGameObject.cpp src/Singletons/TextureManager.cpp src/Vector2D.cpp src/GameObjects/StaticObject.cpp src/GameStates/SinglePlayerMenuState.cpp
        src/GameStates/MultiPlayerMenuState.cpp src/GameObjects/TextSquare.cpp src/GameStates/PauseMenuState.cpp src/Singletons/GameObjectFactory.cpp src/GameStates/StateParser.cpp
        src/GameStates/MenuState.cpp src/Levels/Level.cpp src/Levels/Layer.cpp src/Levels/LevelParser.cpp src/Levels/TileLayer.cpp src/Levels/ObjectLayer.cpp
        src/GameStates/MultiPlayerPlayState.cpp src/GameStates/SinglePlayerPlayState.cpp src/Singletons/CollisionManager.cpp src/GameStates/MultiPlayer1WinState.cpp
        src/GameStates/MultiPlayer2WinState.cpp src/Bonus.cpp src/GameObjects/Player.cpp)

target_include_directories(a PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBXML2_LIBRARIES} SDL2main SDL2 SDL2_image)

