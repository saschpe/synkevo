project(synkevo)
cmake_minimum_required(VERSION 2.8.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(KDE4 REQUIRED)
find_package(SyncEvolution)

set(SyncEvolution_DBUS_SERVER_INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/share/dbus-interfaces/org.syncevolution.Server.xml)
set(SyncEvolution_DBUS_SESSION_INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/share/dbus-interfaces/org.syncevolution.Session.xml)
set(SyncEvolution_DBUS_CONNECTION_INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/share/dbus-interfaces/org.syncevolution.Connection.xml)

include(KDE4Defaults)
include(MacroLibrary)
include(CheckIncludeFiles)

include_directories(${QT_INCLUDES} ${KDE4_INCLUDES})

add_subdirectory(app)
