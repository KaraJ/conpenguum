######################################################################
# Automatically generated by qmake (2.01a) Fri Mar 19 17:52:20 2010
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . comm engine
INCLUDEPATH += . comm engine
QT += xml

# Input
HEADERS += frame.h \
           map.h \
           newtObjects.h \
           physics.h \
           ship.h \
           shot.h \
           comm/commserver.h \
           comm/TCPServer.h \
           engine/ServerEngine.h \
           ../Core/comm/data/clientaction.h \
           ../Core/comm/globals.h \
           ../Core/comm/data/bitmask.h \
           ../Core/comm/data/updateobject.h \
           ../Core/comm/data/servermessage.h \
           ../Core/comm/socketwrapper.h \
           ../Core/Logger.h \
           ../Core/comm/tcpconnection.h \
           ../Core/comm/udpConnection.h \
           ../Core/comm/crc.h
SOURCES += frame.cpp \
           map.cpp \
           physics.cpp \
           ship.cpp \
           shot.cpp \
           comm/commserver.cpp \
           comm/TCPServer.cpp \
           engine/main.cpp \
           engine/ServerEngine.cpp \
           ../Core/comm/data/clientaction.cpp \
           ../Core/comm/data/updateobject.cpp \
           ../Core/comm/data/servermessage.cpp \
           ../Core/comm/socketwrapper.cpp \
           ../Core/Logger.cpp \
           ../Core/comm/tcpconnection.cpp \
           ../Core/comm/udpConnection.cpp \
           ../Core/comm/crc.cpp
