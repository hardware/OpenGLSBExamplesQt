#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Window;
class QWidget;
class QDockWidget;
class ObjectViewer;
class Object3D;
class QLabel;
class QDoubleSpinBox;
class QLCDNumber;

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
    void setViewProperties(bool state);
    void setFramerate();

private:
    QWidget      * m_params,         * m_coordinate;
    QDockWidget  * m_dockParamsArea, * m_dockCoordinateArea, * m_dockMatrixArea;
    ObjectViewer * m_scene;
    Object3D     * m_object3D;

    QScopedPointer<Window> m_openglArea;

    QLabel * fovLabel,   * leftLabel,
           * rightLabel, * bottomLabel,
           * topLabel,   * nearPlaneLabel,
           * farPlaneLabel;

    QDoubleSpinBox * fovValue,      * nearPlaneValue,
                   * farPlaneValue, * leftValue,
                   * rightValue,    * bottomValue,
                   * topValue;

    QLCDNumber* fpsCounter;

};

#endif // MAINWINDOW_H
