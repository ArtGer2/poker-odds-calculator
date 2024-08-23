cmake_minimum_required(VERSION 3.5)

project(card VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Concurrent)

set(TS_FILES card_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
        draggablelabel.h draggablelabel.cpp
        cardchoise.h cardchoise.cpp cardchoise.ui
        droplabel.h droplabel.cpp
        ../../Desktop/images/2_of_clubs.png
        ../../Desktop/images/2_of_diamonds.png ../../Desktop/images/2_of_hearts.png ../../Desktop/images/2_of_spades.png ../../Desktop/images/3_of_clubs.png ../../Desktop/images/3_of_diamonds.png ../../Desktop/images/3_of_hearts.png ../../Desktop/images/3_of_spades.png ../../Desktop/images/4_of_clubs.png ../../Desktop/images/4_of_diamonds.png ../../Desktop/images/4_of_hearts.png ../../Desktop/images/4_of_spades.png ../../Desktop/images/5_of_clubs.png ../../Desktop/images/5_of_diamonds.png ../../Desktop/images/5_of_hearts.png ../../Desktop/images/5_of_spades.png ../../Desktop/images/6_of_clubs.png ../../Desktop/images/6_of_diamonds.png ../../Desktop/images/6_of_hearts.png ../../Desktop/images/6_of_spades.png ../../Desktop/images/7_of_clubs.png ../../Desktop/images/7_of_diamonds.png ../../Desktop/images/7_of_hearts.png ../../Desktop/images/7_of_spades.png ../../Desktop/images/8_of_clubs.png ../../Desktop/images/8_of_diamonds.png ../../Desktop/images/8_of_hearts.png ../../Desktop/images/8_of_spades.png ../../Desktop/images/9_of_clubs.png ../../Desktop/images/9_of_diamonds.png ../../Desktop/images/9_of_hearts.png ../../Desktop/images/9_of_spades.png ../../Desktop/images/10_of_clubs.png ../../Desktop/images/10_of_diamonds.png ../../Desktop/images/10_of_hearts.png ../../Desktop/images/10_of_spades.png ../../Desktop/images/ace_of_clubs.png ../../Desktop/images/ace_of_diamonds.png ../../Desktop/images/ace_of_hearts.png ../../Desktop/images/ace_of_spades.png ../../Desktop/images/ace_of_spades2.png ../../Desktop/images/black_joker.png ../../Desktop/images/jack_of_clubs.png ../../Desktop/images/jack_of_clubs2.png ../../Desktop/images/jack_of_diamonds.png ../../Desktop/images/jack_of_diamonds2.png ../../Desktop/images/jack_of_hearts.png ../../Desktop/images/jack_of_hearts2.png ../../Desktop/images/jack_of_spades.png ../../Desktop/images/jack_of_spades2.png ../../Desktop/images/king_of_clubs.png ../../Desktop/images/king_of_clubs2.png ../../Desktop/images/king_of_diamonds.png ../../Desktop/images/king_of_diamonds2.png ../../Desktop/images/king_of_hearts.png ../../Desktop/images/king_of_hearts2.png ../../Desktop/images/king_of_spades.png ../../Desktop/images/king_of_spades2.png ../../Desktop/images/queen_of_clubs.png ../../Desktop/images/queen_of_clubs2.png ../../Desktop/images/queen_of_diamonds.png ../../Desktop/images/queen_of_diamonds2.png ../../Desktop/images/queen_of_hearts.png ../../Desktop/images/queen_of_hearts2.png ../../Desktop/images/queen_of_spades.png ../../Desktop/images/queen_of_spades2.png ../../Desktop/images/red_joker.png
        images.qrc
        game.h game.cpp
        card.h card.cpp
        hand.h hand.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(card
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

   # qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(card SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(card
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Ссылки на Qt библиотеки для проекта
target_link_libraries(card PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)

# Настройки для macOS и iOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.card)
endif()

set_target_properties(card PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS card
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(card)
endif()
