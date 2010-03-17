TEMPLATE = app
TARGET = Client
QT += core \
    gui \
    xml
HEADERS += panel.h \
    roundrectitem.h \
    splashitem.h \
    Renderer/renderer.h \
    Animation.h \
    Image.h \
    Loader.h \
    BaseWindow.h \
    Comm/Tcpclient.h \
    Comm/Commclient.h \
    Animation/Image.h \
    Animation/qtxmlparse.h \
    Animation/Animation.h \
    main.h
SOURCES += panel.cpp \
    roundrectitem.cpp \
    splashitem.cpp \
    Renderer/renderer.cpp \
    BaseWindow.cpp \
    Comm/Tcpclient.cpp \
    Comm/Commclient.cpp \
    Animation/Image.cpp \
    Animation/qtxmlparse.cpp \
    Animation/Animation.cpp \
    main.cpp
FORMS += backside.ui
contains(QT_CONFIG, opengl):QT += opengl
RESOURCES += menuitems.qrc
LIBS += -lCore \
    -L../Core/Debug
