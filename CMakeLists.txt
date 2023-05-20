cmake_minimum_required(VERSION 3.18)

project(Dungeon C CXX)

set(APP_NAME ${CMAKE_PROJECT_NAME})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/Hero.cpp
    ${PROJECT_SOURCE_DIR}/src/Trigger.cpp
)

if(WIN32)
    add_compile_options(/wd4819)
endif()

add_executable(${APP_NAME} ${SRC_LIST})
target_include_directories(${APP_NAME} PRIVATE ${INCLUDE_DIR})