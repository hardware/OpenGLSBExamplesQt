#include "movingtriangle.h"

#include <math.h>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLDebugLogger>

/**
 * @brief Constructeur paramétré
 *
 * @param parent Objet parent
 */
MovingTriangle::MovingTriangle(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this))
{}

MovingTriangle::~MovingTriangle()
{
    m_vao->destroy();
}

void MovingTriangle::initialize()
{
    // Récupération des fonctions d'OpenGL 4.3
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_4_3_Core>();

    if ( ! m_funcs )
    {
        qFatal("Requires OpenGL >= 4.3");
        exit(1);
    }

    m_funcs->initializeOpenGLFunctions();

    // Initialisation du système de logging
    connect(m_logger, SIGNAL(messageLogged(QOpenGLDebugMessage)), this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if(m_logger->initialize())
        m_logger->enableMessages();

    // Charge, compile et link le Vertex et Fragment Shader
    prepareShaders();

    // Création du Vertex Array Object
    m_vao->create();
    m_vao->bind();
}

void MovingTriangle::update(float t)
{
    Q_UNUSED(t);
}

void MovingTriangle::render(double currentTime)
{
    const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
                              (float)cos(currentTime) * 0.5f + 0.5f,
                              0.0f, 1.0f };

    m_funcs->glClearBufferfv(GL_COLOR, 0, color);

    m_shader->shader()->bind();
    m_shader->shader()->setAttributeValue(1, QVector4D((float)sin(currentTime) * 0.5f,
                                                       (float)cos(currentTime) * 0.6f,
                                                       0.0f, 0.0f));

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MovingTriangle::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void MovingTriangle::prepareShaders()
{
    m_shader = ShadersPtr(new Shaders);

    m_shader->setVertexShader(":/resources/shaders/basic.vert");
    m_shader->setFragmentShader(":/resources/shaders/basic.frag");

    m_shader->shader()->link();
}

void MovingTriangle::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
