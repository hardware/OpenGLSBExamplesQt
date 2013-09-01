#ifndef OBJECTVIEWER_H
#define OBJECTVIEWER_H

#include "abstractscene.h"
#include "shaders.h"
#include "object3d.h"

#include <QOpenGLBuffer>
#include <QOpenGLDebugMessage>

class Camera;
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

    // Contrôle du mouvement de la camera
    void setSideSpeed(float vx) { m_v.setX(vx); }
    void setVerticalSpeed(float vy) { m_v.setY(vy); }
    void setForwardSpeed(float vz) { m_v.setZ(vz); }
    void setViewCenterFixed(bool b) { m_viewCenterFixed = b; }

    // Contrôle de l'orientation de la camera
    void pan(float angle) { m_panAngle = angle; }
    void tilt(float angle) { m_tiltAngle = angle; }

    Object3D* getObject();
    Camera*   getCamera();

public slots:
    void onMessageLogged(QOpenGLDebugMessage message);
    void checkWireframe(int state);

private:
    void prepareShaders();
    void prepareVertexBuffer();

    Camera                    * m_camera;
    QOpenGLVertexArrayObject  * m_vao;
    QOpenGLFunctions_3_2_Core * m_funcs;
    QOpenGLDebugLogger        * m_logger;
    QOpenGLBuffer               m_vertexPositionBuffer;
    QVector<QVector3D>          m_positionVertices;
    QMatrix4x4                  m_projection;

    ShadersPtr m_shader;
    Object3D   m_spinningCube;

    QVector3D m_v;

    bool m_viewCenterFixed;

    float m_panAngle;
    float m_tiltAngle;
    float m_time;

    const float m_metersToUnits;
};

#endif // OBJECTVIEWER_H
