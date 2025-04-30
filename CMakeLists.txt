cmake_minimum_required(VERSION 3.10)
    project(Pilgrim)

    #vcpkg
    find_package(glfw3 CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)


    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    file(GLOB SOURCES "src/*.cpp")

    file(COPY ${CMAKE_SOURCE_DIR}/src/Shaders DESTINATION ${CMAKE_BINARY_DIR}/bin)

    add_executable(${PROJECT_NAME} ${SOURCES} "src/Game.cpp" "src/States/GameStates/MenuGameState.cpp" "src/States/GameStates/PlayingGameState.cpp" "src/States/GameStates/PausedGameState.cpp" "src/States/GameStates/GameStatesFactory.cpp" "src/Renderer.cpp" "vendor/glad/glad.c"    "src/ShaderLoader.cpp" "src/World/TerrainManager.cpp" "src/World/TerrainChunk.cpp" "vendor/sol-prog/PerlinNoise.cpp" "src/World/CloudManager.cpp")

    target_include_directories(${PROJECT_NAME}
        PUBLIC
            include
            vendor
    )



    target_link_libraries(Pilgrim PRIVATE glfw opengl32)
    