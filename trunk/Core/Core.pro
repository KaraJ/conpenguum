SOURCES += comm/socketwrapper.cpp \
    comm/tcpconnection.cpp \
    comm/data/bitmask.cpp \
    comm/data/message.cpp \
    comm/data/servermessage.cpp
HEADERS += comm/socketwrapper.h \
    comm/tcpconnection.h \
    comm/data/bitmask.h \
    comm/data/clientaction.h \
    comm/data/message.h \
    comm/data/servermessage.h \
    comm/data/updateobject.h
TARGET   = core
TEMPLATE = lib
CONFIG	 = staticlib warn_on
