TEMPLATE = app

SOURCES += Animation/Loader.cpp \
    Animation/Image.cpp \
    Animation/Animation.cpp \
    comm/commclient.cpp \
    comm/tcpclient.cpp \
    main.cpp \
    Renderer/renderer.cpp \
    BaseWindow.cpp
		
HEADERS += Animation/Loader.h \
    Animation/Image.h \
    Animation/Animation.h \
    comm/commclient.h \
    comm/tcpclient.h \
    main.h \
    Renderer/renderer.h \
    BaseWindow.h

QT += opengl

