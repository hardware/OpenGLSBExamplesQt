#include "SpinningCubeDUB/ui/window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window window;
    window.show();

    return a.exec();
}
