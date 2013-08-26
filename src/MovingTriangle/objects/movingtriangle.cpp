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
    m_shaderProgram.release();
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
    prepareShaderProgram();

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

    m_shaderProgram.bind();
    m_shaderProgram.setAttributeValue(1, QVector4D((float)sin(currentTime) * 0.5f,
                                                   (float)cos(currentTime) * 0.6f,
                                                   0.0f, 0.0f));

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MovingTriangle::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void MovingTriangle::prepareShaderProgram()
{
    // Charge et compile le Vertex Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resources/shaders/basic.vert") )
        qCritical() << "Could not compile vertex shader. Log : " << m_shaderProgram.log();

    // Charge et compile le Fragment Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resources/shaders/basic.frag") )
        qCritical() << "Could not compile fragment shader. Log : " << m_shaderProgram.log();

    // Permet de linker les shaders
    if( ! m_shaderProgram.link() )
        qCritical() << "Could not link shader program. Log : " << m_shaderProgram.log();

    m_shaderProgram.removeAllShaders();
}

void MovingTriangle::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
