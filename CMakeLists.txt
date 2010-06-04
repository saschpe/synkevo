project(synkevo)
cmake_minimum_required(VERSION 2.8.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(KDE4 REQUIRED)
find_package(SyncEvolution)

include(KDE4Defaults)
include(MacroLibrary)
include(CheckIncludeFiles)

include_directories(${QT_INCLUDES} ${KDE4_INCLUDES})

add_subdirectory(app)
#add_subdirectory(kcm)
#add_subdirectory(part)
