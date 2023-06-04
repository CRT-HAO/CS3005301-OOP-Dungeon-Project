cmake_minimum_required(VERSION 3.18)

project(Dungeon C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_NAME ${CMAKE_PROJECT_NAME})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/core/Room.cpp
    ${PROJECT_SOURCE_DIR}/src/core/ObjectsManager.cpp
    ${PROJECT_SOURCE_DIR}/src/core/Position.cpp
    ${PROJECT_SOURCE_DIR}/src/core/PositionFloat.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

if(MSVC)
    add_compile_options(/wd4819)
endif()

if(APPLE)
    add_link_options(-framework WebKit)
endif()

if(WIN32)
    set(WEBVIEW2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/lib/webview2/build/native/include)
    include_directories(${WEBVIEW2_INCLUDE_DIR})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # using GCC
        add_link_options(-mwindows -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion)
    endif()
endif()

set(WEBVIEW_INCLUDE_DIR ${APP_NAME}/libs/webview)

# add_executable(${APP_NAME} ${SRC_LIST})
add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${SRC_LIST})
target_include_directories(${APP_NAME} PRIVATE ${INCLUDE_DIR} ${WEBVIEW_INCLUDE_DIR})

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

# Set the assets path to "/assets" or "/../Resources/assets" on macOS
if(APPLE)
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/assets")
else()
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/assets")
endif()

# Copy assets to assets path
add_custom_command(TARGET ${APP_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/" "${ASSETS_PATH}")