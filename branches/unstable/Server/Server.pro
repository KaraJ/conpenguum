# DO NOT USE QMAKE TO AUTOGEN THESE, IT DOESN'T WORK

CONFIG += qt debug warn_on
TEMPLATE = app
TARGET = Server
QT += gui core xml
OBJECTS_DIR = obj
INCPATH += -I/usr/include/mysql -I/usr/include/mysql++
# Input
HEADERS += gameplay/Frame.h \
           gameplay/Map.h \
           gameplay/Tile.h \
           gameplay/NewtObjects.h \
           gameplay/Physics.h \
           gameplay/Ship.h \
           gameplay/Shot.h \
           gameplay/general.h \
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
SOURCES += gameplay/Frame.cpp \
           gameplay/Map.cpp \
           gameplay/Tile.cpp \
           gameplay/Physics.cpp \
           gameplay/Ship.cpp \
           gameplay/Shot.cpp \
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
LIBS += -lCore \
	-lmysql \
	-lmysql++ \
	 -L../Core/Debug \
	 -L/usr/lib
