#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QElapsedTimer>

class AbstractScene;
class QOpenGLContext;

/**
 * @class Window
 * @brief Classe representant la zone de rendu OpenGL
 *
 * Cette classe permet d'initialiser le contexte OpenGL et de
 * manipuler la scène de rendu.
 */
class Window : public QWindow
{
    Q_OBJECT

public:
    Window(QScreen *screen = 0);

private:
    void initializeGL();

public slots:
    void checkAnimate(int state);
    void checkWireframe(int state);

    void setObjectXPosition(int x);
    void setObjectYPosition(int y);
    void setObjectZPosition(int z);

    void setObjectXRotation(int x);
    void setObjectYRotation(int y);
    void setObjectZRotation(int z);
protected slots:
    void resizeGL();
    void paintGL();
    void updateScene();

private:
    QElapsedTimer     m_timer;
    QOpenGLContext *  m_context;
    AbstractScene  *  m_scene;
};

#endif // WINDOW_H
