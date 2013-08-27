#ifndef SIMPLETRIANGLEMULTIPLEVBO_H
#define SIMPLETRIANGLEMULTIPLEVBO_H

#include "abstractscene.h"
#include "shaders.h"

#include <QOpenGLBuffer>
#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_3_2_Core;
class QOpenGLDebugLogger;

class SimpleTriangleMultipleVBO : public AbstractScene
{
    Q_OBJECT

public:
    SimpleTriangleMultipleVBO(QObject* parent = 0);
    virtual ~SimpleTriangleMultipleVBO();

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
    QOpenGLBuffer               m_vertexPositionBuffer, m_vertexColorBuffer;
    QVector<QVector4D>          m_positionVertices, m_colorVertices;

    ShadersPtr m_shader;
};

#endif // SIMPLETRIANGLEMULTIPLEVBO_H
