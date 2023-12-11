cmake_minimum_required(VERSION 3.5)

project(RetroWaveMIDIProxyGUI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS SerialPort REQUIRED)


include(cmake/CPM.cmake)
include(cmake/PatchFile.cmake)

CPMAddPackage(
        NAME libADLMIDI
        GITHUB_REPOSITORY Wohlstand/libADLMIDI
        GIT_TAG 84d27bc2bdbd6dd249537a7f7d2450cbd402482e
        GIT_SHALLOW ON
)

CPMAddPackage(
        NAME rtmidi
        GITHUB_REPOSITORY thestk/rtmidi
        GIT_TAG 6.0.0
        GIT_SHALLOW ON
)

if(ANDROID)
  add_library(RetroWaveMIDIProxyGUI SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(RetroWaveMIDIProxyGUI
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
endif()

patch_file(
        ${libADLMIDI_SOURCE_DIR}/src/midi_sequencer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/patch/00-adlmidi-nuke-midisequencer-private.patch
)

target_compile_definitions(ADLMIDI_static PUBLIC -Dprivate=public)

target_link_libraries(RetroWaveMIDIProxyGUI PRIVATE ADLMIDI_static rtmidi Qt5::Widgets Qt5::SerialPort)
target_include_directories(RetroWaveMIDIProxyGUI PUBLIC ${libADLMIDI_SOURCE_DIR}/src/)
