SOURCES += comm/socketwrapper.cpp \
    comm/tcpconnection.cpp \
    comm/data/servermessage.cpp \
    Logger.cpp \
    comm/crc.cpp \
    comm/udpConnection.cpp \
    comm/data/clientaction.cpp \
    comm/data/updateobject.cpp
HEADERS += comm/socketwrapper.h \
    comm/tcpconnection.h \
    comm/crc.h \
    comm/udpConnection.h \
    comm/data/clientaction.h \
    comm/data/servermessage.h \
    comm/data/updateobject.h \
    comm/globals.h \
    Logger.h \
    comm/data/bitmask.h
TARGET = Debug/Core
TEMPLATE = lib
CONFIG = staticlib \
    warn_on \
    qt
QT += core
OBJECTS_DIR = bin
QT += xml
RESOURCES += sharedResources.qrc