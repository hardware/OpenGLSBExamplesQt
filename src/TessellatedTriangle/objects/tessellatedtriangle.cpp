#include "tessellatedtriangle.h"

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
TessellatedTriangle::TessellatedTriangle(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this))
{}

TessellatedTriangle::~TessellatedTriangle()
{
    m_vao->destroy();
}

void TessellatedTriangle::initialize()
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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TessellatedTriangle::update(float t)
{
    Q_UNUSED(t);
}

void TessellatedTriangle::render(double currentTime)
{
    Q_UNUSED(currentTime);

    // Efface le tampon d'affichage
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader->shader()->bind();

    glDrawArrays(GL_PATCHES, 0, 3);
}

void TessellatedTriangle::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void TessellatedTriangle::prepareShaders()
{
    m_shader = ShadersPtr(new Shaders);

    m_shader->setVertexShader(":/resources/shaders/basic.vert");
    m_shader->setTessellationControlShader(":/resources/shaders/basic.tcs");
    m_shader->setTessellationEvaluationShader(":/resources/shaders/basic.tes");
    m_shader->setFragmentShader(":/resources/shaders/basic.frag");

    m_shader->shader()->link();
}

void TessellatedTriangle::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
