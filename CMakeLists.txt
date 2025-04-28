cmake_minimum_required(VERSION 3.19)
project(MultimediaPlayer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia MultimediaWidgets)

qt_standard_project_setup()

qt_add_executable(MultimediaPlayer
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h


)

target_link_libraries(MultimediaPlayer
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        Qt::MultimediaWidgets
)

include(GNUInstallDirs)

install(TARGETS MultimediaPlayer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MultimediaPlayer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
