#include "window.h"

#include "../objects/objectviewer.h"

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
      m_scene(new ObjectViewer(this))
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

    m_timer.invalidate();

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
    m_scene->update(0.0f);
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

/**
 * @brief Vérification de l'activation du mode wireframe
 */
void Window::checkWireframe(int state)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    if(state == Qt::Checked)
      scene->wireframe(true);

    if(state == Qt::Unchecked)
      scene->wireframe(false);
}

void Window::setObjectXPosition(int x)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    scene->m_position.x = (float)x/100;
}

void Window::setObjectYPosition(int y)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    scene->m_position.y = (float)y/100;
}

void Window::setObjectZPosition(int z)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    scene->m_position.z = (float)-z/100;
}

void Window::setObjectXRotation(int x)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    scene->m_rotation.x = (float)x;
}

void Window::setObjectYRotation(int y)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    scene->m_rotation.y = (float)y;
}

void Window::setObjectZRotation(int z)
{
    ObjectViewer* scene = static_cast<ObjectViewer*>(m_scene);

    scene->m_rotation.z = (float)z;
}

