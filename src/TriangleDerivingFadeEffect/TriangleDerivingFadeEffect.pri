QT += opengl

HEADERS += \
    $$PWD/objects/trianglederivingfadeeffect.h \
    $$PWD/objects/abstractscene.h \
    $$PWD/ui/window.h

SOURCES += \
    $$PWD/objects/trianglederivingfadeeffect.cpp \
    $$PWD/objects/abstractscene.cpp \
    $$PWD/ui/window.cpp

RESOURCES += \
    $$PWD/resources.qrc

OTHER_FILES += \
    $$PWD/resources/shaders/basic.vert \
    $$PWD/resources/shaders/basic.frag
