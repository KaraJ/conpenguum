# DO NOT USE QMAKE TO AUTOGEN THESE, IT DOESN'T WORK
QT += core \
    xml
    
HEADERS += Player.h \
    Logger.h \
    ConfigParser.h \
    comm/crc.h \
    comm/globals.h \
    comm/socketwrapper.h \
    comm/tcpconnection.h \
    comm/udpConnection.h \
    resourceMgr/resourceDefinitions.h \
    resourceMgr/resourceEnums.h \
    resourceMgr/resourcemanager.h \
    comm/data/bitmask.h \
    comm/data/clientaction.h \
    comm/data/servermessage.h \
    comm/data/updateobject.h
    
SOURCES += Logger.cpp \
    ConfigParser.cpp \
    comm/crc.cpp \
    comm/socketwrapper.cpp \
    comm/tcpconnection.cpp \
    comm/udpConnection.cpp \
    resourceMgr/resourcemanager.cpp \
    comm/data/clientaction.cpp \
    comm/data/servermessage.cpp \
    comm/data/updateobject.cpp
    
RESOURCES += resources/sharedResources.qrc
TEMPLATE = lib
TARGET = Debug/Core
OBJECTS_DIR = obj

CONFIG += qt \
    staticlib \
    debug \
    warn_on
    
OTHER_FILES += resources/ships.xml \
    resources/shots.xml
