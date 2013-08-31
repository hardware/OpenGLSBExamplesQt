#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Window;
class QWidget;
class QDockWidget;
class ObjectViewer;
class Object3D;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeParamsArea();

private:
    Window       * m_openglArea;
    QWidget      * m_params;
    QDockWidget  * m_dockArea;
    QScopedPointer<ObjectViewer> m_scene;
    QScopedPointer<Object3D>     m_object3D;

protected:
    void keyPressEvent(QKeyEvent* e);

signals:

public slots:

};

#endif // MAINWINDOW_H
