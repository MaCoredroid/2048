
QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    core/board.cpp \
    core/game.cpp \
    gui/qgameboard.cpp \
    core/observer.cpp \
    core/subject.cpp \
    gui/qnumber.cpp \
    core/number.cpp \
    gui/qbutton.cpp \
    gui/qgamenotice.cpp

HEADERS  += \
    core/board.h \
    core/game.h \
    gui/qgameboard.h \
    core/observer.h \
    core/subject.h \
    gui/qnumber.h \
    core/number.h \
    gui/qgamenotice.h \
    gui/qbutton.h

DISTFILES +=
