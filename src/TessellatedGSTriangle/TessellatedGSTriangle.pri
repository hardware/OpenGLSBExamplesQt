QT += opengl

RCC_DIR     = $$PWD/build/tmp/rcc
UI_DIR      = $$PWD/build/tmp/ui
MOC_DIR     = $$PWD/build/tmp/moc
OBJECTS_DIR = $$PWD/build/tmp/obj

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = $$PWD/build/release
}

HEADERS += \
    $$PWD/objects/tessellatedgstriangle.h \
    $$PWD/objects/abstractscene.h \
    $$PWD/ui/window.h

SOURCES += \
    $$PWD/objects/tessellatedgstriangle.cpp \
    $$PWD/objects/abstractscene.cpp \
    $$PWD/ui/window.cpp

RESOURCES += \
    $$PWD/resources.qrc

OTHER_FILES += \
    $$PWD/resources/shaders/basic.vert \
    $$PWD/resources/shaders/basic.frag \
    $$PWD/resources/shaders/basic.tes \
    $$PWD/resources/shaders/basic.tcs \
    $$PWD/resources/shaders/basic.geom

