#include "tessellatedgstriangle.h"

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
TessellatedGSTriangle::TessellatedGSTriangle(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this))
{}

TessellatedGSTriangle::~TessellatedGSTriangle()
{
    m_vao->destroy();
    m_shaderProgram.release();
}

void TessellatedGSTriangle::initialize()
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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(5.0f);
}

void TessellatedGSTriangle::update(float t)
{
    Q_UNUSED(t);
}

void TessellatedGSTriangle::render(double currentTime)
{
    Q_UNUSED(currentTime);

    // Efface le tampon d'affichage
    glClear(GL_COLOR_BUFFER_BIT);

    m_shaderProgram.bind();

    glDrawArrays(GL_PATCHES, 0, 3);
}

void TessellatedGSTriangle::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void TessellatedGSTriangle::prepareShaderProgram()
{
    // Charge et compile le Vertex Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resources/shaders/basic.vert") )
        qCritical() << "Could not compile vertex shader. Log : " << m_shaderProgram.log();

    // Charge et compile le Tessellation Control Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/resources/shaders/basic.tcs") )
        qCritical() << "Could not compile tessellation control shader. Log : " << m_shaderProgram.log();

    // Charge et compile le Tessellation Evaluation Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/resources/shaders/basic.tes") )
        qCritical() << "Could not compile tessellation evaluation shader. Log : " << m_shaderProgram.log();

    // Charge et compile le Geometry Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/resources/shaders/basic.geom") )
        qCritical() << "Could not compile geometry shader. Log : " << m_shaderProgram.log();

    // Charge et compile le Fragment Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resources/shaders/basic.frag") )
        qCritical() << "Could not compile fragment shader. Log : " << m_shaderProgram.log();

    // Permet de linker les shaders
    if( ! m_shaderProgram.link() )
        qCritical() << "Could not link shader program. Log : " << m_shaderProgram.log();

    m_shaderProgram.removeAllShaders();
}

void TessellatedGSTriangle::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
