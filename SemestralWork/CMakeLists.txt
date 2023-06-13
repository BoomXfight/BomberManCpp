cmake_minimum_required(VERSION 3.25)
project(a)

set(CMAKE_CXX_STANDARD 17)

find_package(LibXml2 REQUIRED)

add_executable(a src/Bonus.cpp src/CollisionManager.cpp src/Enemy.cpp src/Game.cpp src/GameObject.cpp src/GameObjectFactory.cpp src/GameState.cpp src/GameStateMachine.cpp src/InputHandler.cpp src/Layer.cpp src/Level.cpp src/LevelParser.cpp src/LoaderParams.cpp src/MainMenuState.cpp src/MenuButton.cpp src/MenuState.cpp src/MultiPlayer1WinState.cpp src/MultiPlayer2WinState.cpp src/MultiPlayerMenuState.cpp src/MultiPlayerPlayState.cpp src/ObjectLayer.cpp src/PauseMenuState.cpp src/Player.cpp src/Player1.cpp src/Player2.cpp src/ScoreboardState.cpp src/SDLGameObject.cpp src/SinglePlayerLostState.cpp src/SinglePlayerMenuState.cpp src/SinglePlayerPlayState.cpp src/SinglePlayerWonState.cpp src/StateParser.cpp src/StaticObject.cpp src/TextSquare.cpp src/TextureManager.cpp src/TileLayer.cpp src/Vector2D.cpp src/main.cpp)

target_include_directories(a PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBXML2_LIBRARIES} SDL2main SDL2 SDL2_image SDL2_ttf)

