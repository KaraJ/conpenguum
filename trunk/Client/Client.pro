TEMPLATE = app
TARGET = Client
QT += core gui xml
HEADERS += Roundrectitem.h \
    Panel.h \
    Splashitem.h \
	BaseWindow.h \
    Comm/Tcpclient.h \
    Comm/Commclient.h \
    Renderer/Renderer.h \
    Animation/Image.h \
    Animation/qtxmlparse.h \
    Animation/Animation.h \
    main.h
SOURCES += Roundrectitem.cpp \
    Panel.cpp \
    Splashitem.cpp \
	BaseWindow.cpp \
    Comm/Tcpclient.cpp \
    Comm/Commclient.cpp \
    Renderer/Renderer.cpp \
    Animation/Image.cpp \
    Animation/qtxmlparse.cpp \
    Animation/Animation.cpp \
    main.cpp
FORMS += backside.ui
contains(QT_CONFIG, opengl):QT += opengl
RESOURCES += menuitems.qrc
LIBS += -lCore \
    -L../Core/Debug
