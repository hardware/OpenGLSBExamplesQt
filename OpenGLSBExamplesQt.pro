# include( src/SimplePoint/SimplePoint.pri )
# include( src/SimpleTriangle/SimpleTriangle.pri )
# include( src/MovingTriangle/MovingTriangle.pri )
# include( src/MovingColoredTriangle/MovingColoredTriangle.pri )
# include( src/TessellatedTriangle/TessellatedTriangle.pri )
# include( src/TessellatedGSTriangle/TessellatedGSTriangle.pri )
# include( src/TriangleDerivingFragColor/TriangleDerivingFragColor.pri )
include( src/TriangleDerivingFadeEffect/TriangleDerivingFadeEffect.pri )

QT += core gui widgets

RCC_DIR     = $$_PRO_FILE_PWD_/build/tmp/rcc
UI_DIR      = $$_PRO_FILE_PWD_/build/tmp/ui
MOC_DIR     = $$_PRO_FILE_PWD_/build/tmp/moc
OBJECTS_DIR = $$_PRO_FILE_PWD_/build/tmp/obj

CONFIG(debug, debug|release) {
    DESTDIR = $$_PRO_FILE_PWD_/build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = $$_PRO_FILE_PWD_/build/release
}

SOURCES += \
    src/main.cpp
