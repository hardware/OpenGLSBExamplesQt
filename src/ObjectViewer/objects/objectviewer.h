#ifndef OBJECTVIEWER_H
#define OBJECTVIEWER_H

#include "abstractscene.h"
#include "shaders.h"
#include "object3d.h"

#include <QOpenGLBuffer>
#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_3_2_Core;
class QOpenGLDebugLogger;

class ObjectViewer : public AbstractScene
{
    Q_OBJECT

public:
    ObjectViewer(QObject* parent = 0);
    virtual ~ObjectViewer();

    virtual void initialize();
    virtual void update(float t);
    virtual void render(double currentTime);
    virtual void resize(int width, int height);

    void wireframe(bool state);

    Object3D* getObject();

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
    QMatrix4x4                  m_projection;

    ShadersPtr m_shader;
    Object3D   spinningCube;

public:
    struct {
        float x;
        float y;
        float z;
    } m_position;

    struct {
        float x;
        float y;
        float z;
    } m_rotation;
};

#endif // OBJECTVIEWER_H
