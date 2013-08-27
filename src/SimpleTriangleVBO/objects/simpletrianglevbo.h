#ifndef SIMPLETRIANGLEVBO_H
#define SIMPLETRIANGLEVBO_H

#include "abstractscene.h"
#include "shaders.h"

#include <QOpenGLBuffer>
#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_3_2_Core;
class QOpenGLDebugLogger;

class SimpleTriangleVBO : public AbstractScene
{
    Q_OBJECT

public:
    SimpleTriangleVBO(QObject* parent = 0);
    virtual ~SimpleTriangleVBO();

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
    QVector<QVector4D>          m_positionVertices;

    ShadersPtr m_shader;
};

#endif // SIMPLETRIANGLEVBO_H
