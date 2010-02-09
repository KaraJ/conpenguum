SOURCES += splashitem.cpp \
    roundrectitem.cpp \
    panel.cpp \
    main.cpp
HEADERS += roundrectitem.h \
    panel.h \
    ui_backside.h \
    splashitem.h
contains(QT_CONFIG, opengl):QT += opengl
RESOURCES += padnavigator.qrc
