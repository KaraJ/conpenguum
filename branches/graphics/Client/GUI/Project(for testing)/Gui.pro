SOURCES += splashitem.cpp \
    roundrectitem.cpp \
    panel.cpp \
    main.cpp
HEADERS += roundrectitem.h \
    panel.h \
    splashitem.h
contains(QT_CONFIG, opengl):QT += opengl
FORMS += backside.ui
RESOURCES += menuitems.qrc
