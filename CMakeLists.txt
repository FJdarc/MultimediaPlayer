cmake_minimum_required(VERSION 4.1)
project(MultimediaPlayer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.3/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Svg
        Network
        Multimedia
        MultimediaWidgets
        REQUIRED)

add_executable(MultimediaPlayer main.cpp
        view/mainwindow.h
        view/mainwindow.cpp
        utils/utils.h
        view/openurl.h
        view/openurl.cpp
        view/controlpanel.h
        view/controlpanel.cpp
        model/playlistmodel.h
        model/playlistmodel.cpp
        view/playlist.h
        view/playlist.cpp
        view/playlistdelegate.h
        view/playlistdelegate.cpp
        view/progressbar.cpp
        view/progressbar.h
)
target_link_libraries(MultimediaPlayer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        Qt::Network
        Qt::Multimedia
        Qt::MultimediaWidgets
)

target_include_directories(MultimediaPlayer PRIVATE
        ${CMAKE_SOURCE_DIR}/view
        ${CMAKE_SOURCE_DIR}/model
        ${CMAKE_SOURCE_DIR}/utils
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    set(PLUGIN_LIST
            "platforms/qwindows"
            "multimedia/ffmpegmediaplugin"
            "multimedia/windowsmediaplugin"
    )
    foreach (PLUGIN ${PLUGIN_LIST})
        if (EXISTS "${QT_INSTALL_PATH}/plugins/${PLUGIN}${DEBUG_SUFFIX}.dll")
            string(REGEX REPLACE "/[^/]*$" "" PLUGIN_DIR "${PLUGIN}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/${PLUGIN_DIR}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/${PLUGIN}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/${PLUGIN_DIR}")
        endif ()
    endforeach ()
    foreach (QT_LIB Core Gui Widgets Svg Network Multimedia MultimediaWidgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
    foreach (FFMPEG_LIBS avcodec-61 avformat-61 avutil-59 swscale-8 swresample-5)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/${FFMPEG_LIBS}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (FFMPEG_LIBS)
endif ()
