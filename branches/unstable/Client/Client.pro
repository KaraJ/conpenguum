# DO NOT USE QMAKE TO AUTOGEN THESE, IT DOESN'T WORK
QT += core \
    gui \
    xml \
    phonon
OBJECTS_DIR = obj
TEMPLATE = app
TARGET = Client
HEADERS += engine/Map.h \
    engine/connectthread.h \
    ../Core/comm/globals.h \
    Animation/Animation.h \
    SoundEffects/SoundEffects.h \
    Animation/AnimationEnum.h \
    Animation/Image.h \
    Animation/qtxmlparse.h \
    Animation/QtXmlParse_global.h \
    Comm/Commclient.h \
    Comm/Tcpclient.h \
    engine/BaseWindow.h \
    engine/GameObject.h \
    engine/main.h \
    engine/Panel.h \
    engine/Roundrectitem.h \
    engine/Splashitem.h \
    engine/ipbox.h \
    Renderer/Renderer.h \
    engine/MapTile.h
SOURCES += engine/Map.cpp \
    engine/connectthread.cpp \
    Animation/Animation.cpp \
    SoundEffects/SoundEffects.cpp \
    Animation/Image.cpp \
    Animation/qtxmlparse.cpp \
    Comm/Commclient.cpp \
    Comm/Tcpclient.cpp \
    engine/BaseWindow.cpp \
    engine/main.cpp \
    engine/Panel.cpp \
    engine/Roundrectitem.cpp \
    engine/Splashitem.cpp \
    engine/ipbox.cpp \
    Renderer/Renderer.cpp \
    engine/MapTile.cpp
RESOURCES += Renderer/textures.qrc \
    menuitems.qrc
FORMS += backside.ui \
    ipbox.ui
contains(QT_CONFIG, opengl):QT += opengl
LIBS += -lCore \
    -L../Core/Debug
CONFIG += qt \
    debug \
    warn_on \
    resources
