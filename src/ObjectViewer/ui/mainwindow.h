#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Window;
class QWidget;
class QDockWidget;
class QLCDNumber;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void initializeParamsArea();

private:
    Window      * m_openglArea;
    QWidget     * m_params;
    QDockWidget * m_dockArea;

protected:
    void keyPressEvent(QKeyEvent* e);

signals:

public slots:

};

#endif // MAINWINDOW_H
