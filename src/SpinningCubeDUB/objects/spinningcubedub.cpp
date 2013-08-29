#include "spinningcubedub.h"

#define _USE_MATH_DEFINES  1 // Include constants defined in math.h
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
SpinningCubeDUB::SpinningCubeDUB(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this)),
      m_vertexPositionBuffer(QOpenGLBuffer::VertexBuffer)
{}

SpinningCubeDUB::~SpinningCubeDUB()
{
    m_vao->destroy();
}

void SpinningCubeDUB::initialize()
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

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void SpinningCubeDUB::update(float t)
{
    Q_UNUSED(t);
}

void SpinningCubeDUB::render(double currentTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_modelViewMatrix.setToIdentity();
    m_modelViewMatrix.translate(sinf(currentTime) * 0.6, 0.0f, -1.5f);
    m_modelViewMatrix.rotate(currentTime/0.02f, 0.0f, 1.0f, 1.0f);
    m_modelViewMatrix.scale(fabs(sinf(currentTime))+0.3f);

    m_shader->shader()->bind();
    m_shader->shader()->setUniformValue("modelViewMatrix", m_modelViewMatrix);
    m_shader->shader()->setUniformValue("projectionMatrix", m_projectionMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SpinningCubeDUB::resize(int width, int height)
{
    glViewport(0, 0, width, height);

    float aspect = (float)width / (float)height;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(75.0f, aspect, 0.1f, 1000.0f);
}

void SpinningCubeDUB::prepareShaders()
{
    m_shader = ShadersPtr(new Shaders);

    m_shader->setVertexShader(":/resources/shaders/basic.vert");
    m_shader->setFragmentShader(":/resources/shaders/basic.frag");

    m_shader->shader()->link();
}

void SpinningCubeDUB::prepareVertexBuffer()
{
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f, -0.25f));

    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f, -0.25f));

    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f, -0.25f));

    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f, -0.25f));

    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f,  0.25f));

    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f,  0.25f));

    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f,  0.25f));

    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f,  0.25f));

    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f, -0.25f));

    m_positionVertices.push_back(QVector3D( 0.25f, -0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f, -0.25f,  0.25f));

    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f, -0.25f));
    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f,  0.25f));

    m_positionVertices.push_back(QVector3D( 0.25f,  0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f,  0.25f));
    m_positionVertices.push_back(QVector3D(-0.25f,  0.25f, -0.25f));

    m_vertexPositionBuffer.create();
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexPositionBuffer.bind();
    m_vertexPositionBuffer.allocate(m_positionVertices.constData(), m_positionVertices.size() * sizeof(QVector3D));

    m_shader->shader()->bind();

    m_vertexPositionBuffer.bind();
    m_shader->shader()->enableAttributeArray("vertexPosition");
    m_shader->shader()->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);
}

void SpinningCubeDUB::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}
