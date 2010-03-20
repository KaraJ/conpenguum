QT += core gui xml
TEMPLATE = app
TARGET = Client
# Input
HEADERS += Animation/Animation.h \
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
    Renderer/Renderer.h
SOURCES += Animation/Animation.cpp \
    Animation/Image.cpp \
    Animation/qtxmlparse.cpp \
    Comm/Commclient.cpp \
    Comm/Tcpclient.cpp \
    engine/BaseWindow.cpp \
    engine/main.cpp \
    engine/Panel.cpp \
    engine/Roundrectitem.cpp \
    engine/Splashitem.cpp \
    Renderer/Renderer.cpp
RESOURCES += menuitems.qrc
FORMS += backside.ui
contains(QT_CONFIG, opengl):QT += opengl
LIBS += -lCore \
    -L../Core/Debug



