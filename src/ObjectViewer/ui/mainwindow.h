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

    void initializeMenuBar();
    void initializeParamsArea();

private slots:
    void setFullScreen(bool state);

private:
    QWidget      * m_params;
    QDockWidget  * m_dockArea;
    ObjectViewer * m_scene;
    Object3D     * m_object3D;

    QScopedPointer<Window> m_openglArea;

};

#endif // MAINWINDOW_H
