QT += opengl

INCLUDEPATH += $$_PRO_FILE_PWD_/src/common

HEADERS += \
    $$PWD/objects/movingcoloredtriangle.h \
    $$PWD/ui/window.h

SOURCES += \
    $$PWD/objects/movingcoloredtriangle.cpp \
    $$PWD/ui/window.cpp

RESOURCES += \
    $$PWD/resources.qrc

OTHER_FILES += \
    $$PWD/resources/shaders/basic.vert \
    $$PWD/resources/shaders/basic.frag

