QT += opengl

INCLUDEPATH += $$_PRO_FILE_PWD_/src/common

HEADERS += \
    $$PWD/objects/objectviewer.h \
    $$PWD/ui/window.h \
    $$PWD/ui/mainwindow.h

SOURCES += \
    $$PWD/objects/objectviewer.cpp \
    $$PWD/ui/window.cpp \
    $$PWD/ui/mainwindow.cpp

RESOURCES += \
    $$PWD/resources.qrc

OTHER_FILES += \
    $$PWD/resources/shaders/basic.vert \
    $$PWD/resources/shaders/basic.frag

