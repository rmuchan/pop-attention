cmake_minimum_required(VERSION 3.15)

set(PLUGIN_NAME "pop-attention")
set(QT_LIB /media/scnm/G/Qt5.7.1/5.7/gcc_64/lib)

project(${PLUGIN_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_LIB}/cmake)
set(ENV{PKG_CONFIG_PATH} $ENV{PKG_CONFIG_PATH}:${QT_LIB}/pkgconfig)

find_package(Qt5Widgets REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(DdeDockInterface REQUIRED dde-dock)
pkg_check_modules(DFrameworkDBus REQUIRED dframeworkdbus)
pkg_check_modules(QDBusExtended REQUIRED dbusextended-qt5)

add_definitions("-DQT_PLUGIN")

add_library(${PLUGIN_NAME} SHARED pop_attention_plugin.h pop_attention_plugin.cpp)

set_target_properties(${PLUGIN_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ./)

target_include_directories(${PLUGIN_NAME} PUBLIC
        ${Qt5Widgets_INCLUDE_DIRS}
        ${DdeDockInterface_INCLUDE_DIRS}
        ${DFrameworkDBus_INCLUDE_DIRS}
        ${QDBusExtended_INCLUDE_DIRS}
        )

target_link_directories(${PLUGIN_NAME} PRIVATE ${QT_LIB})
target_link_libraries(${PLUGIN_NAME} PRIVATE
        ${Qt5Widgets_LIBRARIES}
        ${DdeDockInterface_LIBRARIES}
        ${DFrameworkDBus_LIBRARIES}
        ${QDBusExtended_LIBRARIES}
        )

set(CMAKE_INSTALL_PREFIX "/usr")
install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION lib/dde-dock/plugins)
