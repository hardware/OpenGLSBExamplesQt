#include "objectviewer.h"
#include "camera.h"

#define _USE_MATH_DEFINES  1 // Include constants defined in math.h
#include <math.h>

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
      m_camera(new Camera(this)),
      m_vao(new QOpenGLVertexArrayObject(this)),
      m_logger(new QOpenGLDebugLogger(this)),
      m_vertexPositionBuffer(QOpenGLBuffer::VertexBuffer),
      m_panAngle(0.0f),
      m_tiltAngle(0.0f),
      m_v(),
      m_viewCenterFixed(false),
      m_metersToUnits(0.05f),
      m_time(0.0f)

{
    // Initialisation de la position et de l'orientation de la camera
    m_camera->setPosition(QVector3D(0.0f, 0.6f, 2.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    m_camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
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
    const float dt = t - m_time;
    m_time = t;

    Camera::CameraTranslationOption option = m_viewCenterFixed
                                           ? Camera::DontTranslateViewCenter
                                           : Camera::TranslateViewCenter;

    m_camera->translate(m_v * dt * m_metersToUnits, option);

    if( ! qFuzzyIsNull(m_panAngle) )
    {
        m_camera->pan(m_panAngle, QVector3D(0.0f, 1.0f, 0.0f));
        m_panAngle = 0.0f;
    }

    if ( ! qFuzzyIsNull(m_tiltAngle) )
    {
        m_camera->tilt(m_tiltAngle);
        m_tiltAngle = 0.0f;
    }
}

void ObjectViewer::render(double currentTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(currentTime > 0)
    {
        m_spinningCube.rotateY(currentTime/0.02f);
    }

    QMatrix4x4 mvp = m_camera->viewProjectionMatrix() *
                     m_spinningCube.modelMatrix();

    m_shader->shader()->bind();
    m_shader->shader()->setUniformValue("mvp", mvp);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    emit renderCycleDone();
}

void ObjectViewer::resize(int width, int height)
{
    glViewport(0, 0, width, height);

    float aspect = static_cast<float>(width) / static_cast<float>(height);

    m_camera->setPerspectiveProjection(m_camera->fieldOfView(), aspect, m_camera->nearPlane(), m_camera->farPlane());
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
    m_vertexPositionBuffer.release();

    m_shader->shader()->bind();

    m_vertexPositionBuffer.bind();
    m_shader->shader()->enableAttributeArray("vertexPosition");
    m_shader->shader()->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);
}

void ObjectViewer::onMessageLogged(QOpenGLDebugMessage message)
{
    qDebug() << message;
}

void ObjectViewer::toggleFill(bool state)
{
    if(state)
    {
        glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void ObjectViewer::toggleWireframe(bool state)
{
    if(state)
    {
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

void ObjectViewer::togglePoints(bool state)
{
    if(state)
    {
        glDisable(GL_CULL_FACE);
        glPointSize(2.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}

Object3D* ObjectViewer::getObject()
{
    return &m_spinningCube;
}

Camera* ObjectViewer::getCamera()
{
    return m_camera;
}
