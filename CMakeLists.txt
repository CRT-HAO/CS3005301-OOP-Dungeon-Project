cmake_minimum_required(VERSION 3.21)

project(Dungeon C CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_NAME ${CMAKE_PROJECT_NAME})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/core/Entity.cpp
    ${PROJECT_SOURCE_DIR}/src/core/Room.cpp
    ${PROJECT_SOURCE_DIR}/src/core/World.cpp
    ${PROJECT_SOURCE_DIR}/src/core/Player.cpp
    ${PROJECT_SOURCE_DIR}/src/core/Camera.cpp
    ${PROJECT_SOURCE_DIR}/src/core/ObjectManager.cpp
    ${PROJECT_SOURCE_DIR}/src/core/EntityManager.cpp
    ${PROJECT_SOURCE_DIR}/src/core/AnimationManager.cpp
    ${PROJECT_SOURCE_DIR}/src/core/Position.cpp
    ${PROJECT_SOURCE_DIR}/src/core/PositionFloat.cpp
    ${PROJECT_SOURCE_DIR}/src/core/KeyInput.cpp
    ${PROJECT_SOURCE_DIR}/src/core/Game.cpp
    ${PROJECT_SOURCE_DIR}/src/core/block/Block.cpp
    ${PROJECT_SOURCE_DIR}/src/core/block/Ground.cpp
    ${PROJECT_SOURCE_DIR}/src/core/block/Wall.cpp
    ${PROJECT_SOURCE_DIR}/src/core/block/Torch.cpp
    ${PROJECT_SOURCE_DIR}/src/core/block/Door.cpp
    ${PROJECT_SOURCE_DIR}/src/core/block/Heal.cpp
    ${PROJECT_SOURCE_DIR}/src/core/CreatureManager.cpp
    ${PROJECT_SOURCE_DIR}/src/core/creature/Creature.cpp
    ${PROJECT_SOURCE_DIR}/src/core/creature/CreatureS.cpp
    ${PROJECT_SOURCE_DIR}/src/core/creature/ai_engine/AICreatureEngine.cpp
    ${PROJECT_SOURCE_DIR}/src/core/Weapon.cpp
    ${PROJECT_SOURCE_DIR}/src/core/WorldGenerator.cpp
    ${PROJECT_SOURCE_DIR}/src/core/GUIManager.cpp
    ${PROJECT_SOURCE_DIR}/src/core/gui/PlayerGUI.cpp
    ${PROJECT_SOURCE_DIR}/src/core/gui/GameGUI.cpp
    ${PROJECT_SOURCE_DIR}/src/core/GameData.cpp
    ${PROJECT_SOURCE_DIR}/src/core/GameSave.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp)

if(MSVC)
    add_compile_options(/wd4819)
endif()

# add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${SRC_LIST})
add_executable(${APP_NAME} ${SRC_LIST})
target_include_directories(${APP_NAME} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${APP_NAME} PRIVATE sfml-graphics)
target_compile_features(${APP_NAME} PRIVATE cxx_std_17)

if(WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${APP_NAME}> $<TARGET_FILE_DIR:${APP_NAME}> COMMAND_EXPAND_LISTS)
endif()

# install(TARGETS ${APP_NAME})
set_target_properties(${APP_NAME} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER edu.ntust.${APP_NAME}
    MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/Info.plist.in
)

if(APPLE)
    # Enable High-DPI on macOS through our custom Info.plist template
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist.in)
endif()

if(MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

# Set the resources path to "/resources" or "/../Resources/resources" on macOS
if(APPLE)
    # set(RES_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/resources")
    set(RES_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/resources")
else()
    set(RES_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/resources")
endif()

# Copy resources to resources path
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources/" "${RES_PATH}")