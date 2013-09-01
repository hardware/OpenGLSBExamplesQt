#include "window.h"

#include "../objects/objectviewer.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QOpenGLContext>
#include <QTimer>

/**
 * @brief Constructeur paramétré
 *
 * Permet d'initialiser la fenêtre et les propriétés de la zone de rendu OpenGL
 *
 * @param screen Propriétés de l'écran
 */
Window::Window(QScreen *screen)
    : QWindow(screen),
      m_scene(new ObjectViewer(this)),
      m_leftButtonPressed(false)
{
    // On définit le type de la zone de rendu, dans notre cas il
    // s'agit d'une zone OpenGL
    setSurfaceType(QSurface::OpenGLSurface);

    // Puis on définit les propriétés de la zone de rendu
    QSurfaceFormat format;

    format.setDepthBufferSize(24);
    format.setMajorVersion(4);
    format.setMinorVersion(3);
    format.setSamples(4); // Multisampling x4
    format.setProfile(QSurfaceFormat::CoreProfile); // Fonctions obsolètes d'OpenGL non disponibles
    format.setOption(QSurfaceFormat::DebugContext);

    // On applique le format et on créer la fenêtre
    setFormat(format);
    create();
    resize(800, 600);
    setTitle("OpenGLSBExamplesQt - ObjectViewer");

    // On créer le contexte OpenGL et on définit son format
    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();
    m_context->makeCurrent(this);

    // On définit le contexte OpenGL de la scène
    m_scene->setContext(m_context);

    //m_timer.invalidate();
    m_timer.start();

    initializeGL();

    connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGL()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGL()));

    resizeGL();

    // Création d'un timer permettant la mise à jour de la zone de rendu 60 fois par seconde
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(16); // f = 1 / 16.10e-3 = 60Hz
}

/**
 * @brief Initialisation de la zone de rendu
 */
void Window::initializeGL()
{
    m_context->makeCurrent(this);
    m_scene->initialize();
}

/**
 * @brief Mise à jour de la zone de rendu (redessine la scène)
 */
void Window::paintGL()
{
    m_context->makeCurrent(this);
    m_scene->render(static_cast<double>(m_timer.elapsed())/1000);
    m_context->swapBuffers(this);
}

/**
 * @brief Permet de redimensionner la zone de rendu
 */
void Window::resizeGL()
{
    m_context->makeCurrent(this);
    m_scene->resize(width(), height());
}

/**
 * @brief Mise à jour de la scène
 */
void Window::updateScene()
{
    m_scene->update(static_cast<float>(m_timer.elapsed())/1000.0f);
    paintGL();
}

/**
 * @brief Vérification de l'animation de la scène
 */
void Window::checkAnimate(int state)
{
    if(state == Qt::Checked)
        m_timer.start();

    if(state == Qt::Unchecked)
        m_timer.invalidate();
}

ObjectViewer* Window::getScene()
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    return scene;
}

void Window::keyPressEvent(QKeyEvent* e)
{
    const float speed = 44.7f; // in m/s. Equivalent to 100 miles/hour

    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    switch (e->key())
    {
    case Qt::Key_Escape:

        QCoreApplication::instance()->quit();
        break;

    case Qt::Key_Right:
        scene->setSideSpeed(speed);
        break;

    case Qt::Key_Left:
        scene->setSideSpeed(-speed);
        break;

    case Qt::Key_Up:
        scene->setForwardSpeed(speed);
        break;

    case Qt::Key_Down:
        scene->setForwardSpeed(-speed);
        break;

    case Qt::Key_PageUp:
        scene->setVerticalSpeed(speed);
        break;

    case Qt::Key_PageDown:
        scene->setVerticalSpeed(-speed);
        break;

    case Qt::Key_Shift:
        scene->setViewCenterFixed(true);
        break;

    default:
        QWindow::keyPressEvent(e);
    }
}

void Window::keyReleaseEvent(QKeyEvent* e)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    switch (e->key())
    {
        case Qt::Key_Right:
        case Qt::Key_Left:
            scene->setSideSpeed(0.0f);
            break;

        case Qt::Key_Up:
        case Qt::Key_Down:
            scene->setForwardSpeed(0.0f);
            break;

        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            scene->setVerticalSpeed(0.0f);
            break;

        case Qt::Key_Shift:
            scene->setViewCenterFixed(false);
            break;

        default:
            QWindow::keyReleaseEvent(e);
    }
}

void Window::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = true;
        m_pos = m_prevPos = e->pos();
    }

    QWindow::mousePressEvent(e);
}

void Window::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = false;
    }

    QWindow::mouseReleaseEvent(e);
}

void Window::mouseMoveEvent(QMouseEvent* e)
{
    if(m_leftButtonPressed)
    {
        m_pos = e->pos();

        float dx = 0.2f * (m_pos.x() - m_prevPos.x());
        float dy = -0.2f * (m_pos.y() - m_prevPos.y());

        m_prevPos = m_pos;

        ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

        scene->pan(dx);
        scene->tilt(dy);
    }

    QWindow::mouseMoveEvent(e);
}

