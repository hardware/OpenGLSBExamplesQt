#include "trianglederivingfadeeffect.h"

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
TriangleDerivingFadeEffect::TriangleDerivingFadeEffect(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this))
{}

TriangleDerivingFadeEffect::~TriangleDerivingFadeEffect()
{
    m_vao->destroy();
}

void TriangleDerivingFadeEffect::initialize()
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

void TriangleDerivingFadeEffect::update(float t)
{
    Q_UNUSED(t);
}

void TriangleDerivingFadeEffect::render(double currentTime)
{
    const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
                              (float)cos(currentTime) * 0.5f + 0.5f,
                              0.0f, 1.0f };

    m_funcs->glClearBufferfv(GL_COLOR, 0, color);
    m_shader->shader()->bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleDerivingFadeEffect::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void TriangleDerivingFadeEffect::prepareShaders()
{
    m_shader = ShadersPtr(new Shaders);

    m_shader->setVertexShader(":/resources/shaders/basic.vert");
    m_shader->setFragmentShader(":/resources/shaders/basic.frag");

    m_shader->shader()->link();
}

void TriangleDerivingFadeEffect::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
