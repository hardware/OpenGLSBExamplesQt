#ifndef SPINNINGCUBEDUB_H
#define SPINNINGCUBEDUB_H

#include "abstractscene.h"
#include "shaders.h"

#include <QOpenGLBuffer>
#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_3_2_Core;
class QOpenGLDebugLogger;

class SpinningCubeDUB : public AbstractScene
{
    Q_OBJECT

public:
    SpinningCubeDUB(QObject* parent = 0);
    virtual ~SpinningCubeDUB();

    virtual void initialize();
    virtual void update(float t);
    virtual void render(double currentTime);
    virtual void resize(int width, int height);

public slots:
    void onMessageLogged(QOpenGLDebugMessage message);

private:
    void prepareShaders();
    void prepareVertexBuffer();

    QOpenGLVertexArrayObject  * m_vao;
    QOpenGLFunctions_3_2_Core * m_funcs;
    QOpenGLDebugLogger        * m_logger;
    QOpenGLBuffer               m_vertexPositionBuffer;
    QVector<QVector3D>          m_positionVertices;
    QMatrix4x4                  m_modelViewMatrix, m_projectionMatrix;

    ShadersPtr m_shader;
};

#endif // SPINNINGCUBEDUB_H
