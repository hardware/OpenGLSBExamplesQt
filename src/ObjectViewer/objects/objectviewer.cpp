#include "objectviewer.h"

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
ObjectViewer::ObjectViewer(QObject *parent)
    : AbstractScene(parent),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this)),
      m_vertexPositionBuffer(QOpenGLBuffer::VertexBuffer)
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_position.z = 0.0f;
}

ObjectViewer::~ObjectViewer()
{
    m_vao->destroy();
}

void ObjectViewer::initialize()
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

void ObjectViewer::update(float t)
{
    Q_UNUSED(t);
}

void ObjectViewer::render(double currentTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 model, view, mvp;

    view.lookAt(QVector3D(2.0f, 0.6f, 0.0f),  // Position vector
                QVector3D(0.0f, 0.0f, 0.0f),  // LookAt vector
                QVector3D(0.0f, 1.0f, 0.0f)); // Direction vector

    model.translate(m_position.x, m_position.y, m_position.z);
    model.rotate(currentTime/0.02f, 0.0f, 1.0f, 0.0f);
    model.rotate(m_rotation.x, 1.0f, 0.0f, 0.0f);
    model.rotate(m_rotation.y, 0.0f, 1.0f, 0.0f);
    model.rotate(m_rotation.z, 0.0f, 0.0f, 1.0f);

    mvp = m_projection * view * model;

    m_shader->shader()->bind();
    m_shader->shader()->setUniformValue("mvp", mvp);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ObjectViewer::resize(int width, int height)
{
    glViewport(0, 0, width, height);

    float aspect = (float)width / (float)height;

    m_projection.setToIdentity();
    m_projection.perspective(75.0f, aspect, 0.1f, 1000.0f);
}

void ObjectViewer::prepareShaders()
{
    m_shader = ShadersPtr(new Shaders);

    m_shader->setVertexShader(":/resources/shaders/basic.vert");
    m_shader->setFragmentShader(":/resources/shaders/basic.frag");

    m_shader->shader()->link();
}

void ObjectViewer::prepareVertexBuffer()
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

void ObjectViewer::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}

void ObjectViewer::wireframe(bool state)
{
    if(state)
    {
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
