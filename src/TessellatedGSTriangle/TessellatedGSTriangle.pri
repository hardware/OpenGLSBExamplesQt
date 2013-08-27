QT += opengl

HEADERS += \
    $$PWD/objects/tessellatedgstriangle.h \
    $$PWD/ui/window.h

SOURCES += \
    $$PWD/objects/tessellatedgstriangle.cpp \
    $$PWD/ui/window.cpp

RESOURCES += \
    $$PWD/resources.qrc

OTHER_FILES += \
    $$PWD/resources/shaders/basic.vert \
    $$PWD/resources/shaders/basic.frag \
    $$PWD/resources/shaders/basic.tes \
    $$PWD/resources/shaders/basic.tcs \
    $$PWD/resources/shaders/basic.geom

