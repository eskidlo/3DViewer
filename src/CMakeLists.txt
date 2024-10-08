cmake_minimum_required(VERSION 3.5)

project(3dViewer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} /view/glview.h)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)


set(PROJECT_SOURCES
        view/mainwindow.cc
        view/mainwindow.h
        view/glview.cc
        view/glview.h
        view/mainwindow.ui
        controller/controller.h
        controller/controller.cc
        model/adapter.cc
        model/adapter.h
        model/builder.cc
        model/builder.h
        model/facade.cc
        model/facade.h
        model/matrix.cc
        model/matrix.h
        model/parser.cc
        model/parser.h
        main.cc
        ./extra/gif/src/gifimage/qgifglobal.h
        ./extra/gif/src/gifimage/qgifimage.h
        ./extra/gif/src/gifimage/qgifimage_p.h
        ./extra/gif/src/gifimage/qgifimage.cpp
        ./extra/gif/src/3rdParty/giflib/dgif_lib.c
        ./extra/gif/src/3rdParty/giflib/egif_lib.c
        ./extra/gif/src/3rdParty/giflib/gif_err.c
        ./extra/gif/src/3rdParty/giflib/gif_hash.c
        ./extra/gif/src/3rdParty/giflib/gifalloc.c
        ./extra/gif/src/3rdParty/giflib/quantize.c
        ./extra/gif/src/3rdParty/giflib/gif_lib.h
        ./extra/gif/src/3rdParty/giflib/gif_lib_private.h
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3dViewer 
        MANUAL_FINALIZATION 
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET s21_3dviewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

else() 
    if (ANDROID) 
        add_library(3dViewer SHARED 
        ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else() 
        add_executable(3dViewer 
            ${PROJECT_SOURCES}
        ) 
    endif() 
endif()

target_link_libraries(3dViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets) 
target_link_libraries(3dViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(3dViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3dViewer PRIVATE Qt${QT_VERSION_MAJOR}::Gui)

set_target_properties(3dViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com 
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION} 
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} 
    MACOSX_BUNDLE TRUE 
    WIN32_EXECUTABLE TRUE
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3dViewer)
endif()
