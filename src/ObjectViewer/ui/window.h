#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QElapsedTimer>

class AbstractScene;
class QOpenGLContext;
class ObjectViewer;

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

    ObjectViewer* getScene();

private:
    void initializeGL();

public slots:
    void checkAnimate(int state);

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
