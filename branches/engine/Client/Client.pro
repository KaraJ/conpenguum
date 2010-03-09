TEMPLATE = app
TARGET = Client
QT += core    gui
HEADERS += Roundrectitem.h \
    Panel.h \
    Splashitem.h \
    Comm/Tcpclient.h \
    Comm/Commclient.h \
    Renderer/Renderer.h \
    Animation/Loader.h \
    Animation/Image.h \
    Animation/Animation.h \
    main.h
SOURCES += Roundrectitem.cpp \
    Panel.cpp \
    Splashitem.cpp \
    Comm/Tcpclient.cpp \
    Comm/Commclient.cpp \
    Renderer/Renderer.cpp \
    Animation/Loader.cpp \
    Animation/Image.cpp \
    Animation/Animation.cpp \
    main.cpp
FORMS += backside.ui
contains(QT_CONFIG, opengl):QT += opengl
RESOURCES += menuitems.qrc
LIBS += -lCore \
    -L../Core/Debug
