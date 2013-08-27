#ifndef MOVINGCOLOREDTRIANGLE_H
#define MOVINGCOLOREDTRIANGLE_H

#include "abstractscene.h"
#include "shaders.h"

#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_4_3_Core;
class QOpenGLDebugLogger;

class MovingColoredTriangle : public AbstractScene
{
    Q_OBJECT

public:
    MovingColoredTriangle(QObject* parent = 0);
    virtual ~MovingColoredTriangle();

    virtual void initialize();
    virtual void update(float t);
    virtual void render(double currentTime);
    virtual void resize(int width, int height);

public slots:
    void onMessageLogged(QOpenGLDebugMessage message);

private:
    void prepareShaders();

    QOpenGLVertexArrayObject  * m_vao;
    QOpenGLFunctions_4_3_Core * m_funcs;
    QOpenGLDebugLogger        * m_logger;

    ShadersPtr m_shader;
};

#endif // MOVINGCOLOREDTRIANGLE_H
