CONFIG = qt
SOURCES += map.cpp \
	physics.cpp \
    frame.cpp \
    main.cpp \
    ship.cpp \
    shot.cpp \
	comm/TCPServer.cpp \
    comm/commserver.cpp
HEADERS += map.h \
	physics.h \
    frame.h \
    newtObjects.h \
    main.h \
    ship.h \
    shot.h \
	comm/TCPServer.h \
    comm/commserver.h
LIBS += -lCore -L../Core/Debug
QT += gui core
