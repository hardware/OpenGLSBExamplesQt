QT += opengl

HEADERS += \
    $$PWD/objects/movingtriangle.h \
    $$PWD/ui/window.h

SOURCES += \
    $$PWD/objects/movingtriangle.cpp \
    $$PWD/ui/window.cpp

RESOURCES += \
    $$PWD/resources.qrc

OTHER_FILES += \
    $$PWD/resources/shaders/basic.vert \
    $$PWD/resources/shaders/basic.frag

