#configure_file(${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_SOURCE_DIR}/config.h)

set(synkevo_SRCS
    src/gui/config/generalconfig.cpp
    src/gui/widgets/configwidget.cpp
    src/gui/widgets/stateoverlay.cpp
    src/gui/widgets/syncwidget.cpp
    src/gui/mainwindow.cpp
    src/main.cpp
)

set(synkevo_UIS
    src/gui/config/generalconfig.ui
    src/gui/widgets/configwidget.ui
    src/gui/widgets/stateoverlay.ui
    src/gui/widgets/syncwidget.ui
)

qt4_add_dbus_interface(synkevo_SRCS ${SyncEvolution_DBUS_SERVER_INTERFACE} server_interface)
qt4_add_dbus_interface(synkevo_SRCS ${SyncEvolution_DBUS_SESSION_INTERFACE} session_interface)
qt4_add_dbus_interface(synkevo_SRCS ${SyncEvolution_DBUS_CONNECTION_INTERFACE} connection_interface)

kde4_add_ui_files(synkevo_SRCS ${synkevo_UIS})
kde4_add_kcfg_files(synkevo_SRCS src/preferences.kcfgc)
kde4_add_app_icon(synkevo_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/hi*-app-synkevo.png")
kde4_add_executable(synkevo ${synkevo_SRCS})

target_link_libraries(synkevo ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS})

install(TARGETS synkevo ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES src/synkevo.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES src/gui/synkevo.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES src/gui/synkevoui.rc DESTINATION ${DATA_INSTALL_DIR}/synkevo)
install(FILES sounds/synkevo.notifyrc DESTINATION ${DATA_INSTALL_DIR}/synkevo)
