#include "simplepoint.h"

#include <math.h>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLDebugLogger>

/**
 * @brief Constructeur paramétré
 *
 * @param parent Objet parent
 */
SimplePoint::SimplePoint(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this))
{}

SimplePoint::~SimplePoint()
{
    m_vao->destroy();
}

void SimplePoint::initialize()
{
    // Récupération des fonctions d'OpenGL 3.2
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_2_Core>();

    if ( ! m_funcs )
    {
        qFatal("Requires OpenGL >= 3.2");
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

void SimplePoint::update(float t)
{
    Q_UNUSED(t);
}

void SimplePoint::render(double currentTime)
{
    Q_UNUSED(currentTime);

    static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    m_funcs->glClearBufferfv(GL_COLOR, 0, red);

    m_shader->shader()->bind();

    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

void SimplePoint::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void SimplePoint::prepareShaders()
{
    m_shader = ShadersPtr(new Shaders);

    m_shader->setVertexShader(":/resources/shaders/basic.vert");
    m_shader->setFragmentShader(":/resources/shaders/basic.frag");

    m_shader->shader()->link();
}

void SimplePoint::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
