#include "simpletrianglemultiplevbo.h"

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
SimpleTriangleMultipleVBO::SimpleTriangleMultipleVBO(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this)),
      m_vertexPositionBuffer(QOpenGLBuffer::VertexBuffer),
      m_vertexColorBuffer(QOpenGLBuffer::VertexBuffer)
{}

SimpleTriangleMultipleVBO::~SimpleTriangleMultipleVBO()
{
    m_vao->destroy();
}

void SimpleTriangleMultipleVBO::initialize()
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

    // Création du Vertex Array Object
    m_vao->create();
    m_vao->bind();

    // Charge, compile et link le Vertex et Fragment Shader
    prepareShaders();

    // Initialisation du Vertex Buffer Object (VBO)
    prepareVertexBuffer();
}

void SimpleTriangleMultipleVBO::update(float t)
{
    Q_UNUSED(t);
}

void SimpleTriangleMultipleVBO::render(double currentTime)
{
    Q_UNUSED(currentTime);

    glClear(GL_COLOR_BUFFER_BIT);
    m_shader->shader()->bind();
    glDrawArrays(GL_TRIANGLES, 0, m_positionVertices.size());
}

void SimpleTriangleMultipleVBO::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void SimpleTriangleMultipleVBO::prepareShaders()
{
    m_shader = ShadersPtr(new Shaders);

    m_shader->setVertexShader(":/resources/shaders/basic.vert");
    m_shader->setFragmentShader(":/resources/shaders/basic.frag");

    m_shader->shader()->link();
}

void SimpleTriangleMultipleVBO::prepareVertexBuffer()
{
    m_positionVertices.push_back(QVector4D( 0.25f, -0.25f, 0.5f, 1.0f));
    m_positionVertices.push_back(QVector4D(-0.25f, -0.25f, 0.5f, 1.0f));
    m_positionVertices.push_back(QVector4D( 0.25f,  0.25f, 0.5f, 1.0f));

    m_colorVertices.push_back(QVector4D(1.0f, 0.0f, 0.0f, 1.0f));
    m_colorVertices.push_back(QVector4D(0.0f, 1.0f, 0.0f, 1.0f));
    m_colorVertices.push_back(QVector4D(0.0f, 0.0f, 1.0f, 1.0f));

    m_vertexPositionBuffer.create();
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexPositionBuffer.bind();
    m_vertexPositionBuffer.allocate(m_positionVertices.constData(), m_positionVertices.size() * sizeof(QVector4D));

    m_vertexColorBuffer.create();
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexColorBuffer.bind();
    m_vertexColorBuffer.allocate(m_colorVertices.constData(), m_colorVertices.size() * sizeof(QVector4D));

    m_shader->shader()->bind();

    m_vertexPositionBuffer.bind();
    m_shader->shader()->enableAttributeArray("vertexPosition");
    m_shader->shader()->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 4);

    m_vertexColorBuffer.bind();
    m_shader->shader()->enableAttributeArray("vertexColor");
    m_shader->shader()->setAttributeBuffer("vertexColor", GL_FLOAT, 0, 4);
}

void SimpleTriangleMultipleVBO::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
