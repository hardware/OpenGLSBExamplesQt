#ifndef TRIANGLEDERIVINGFADEEFFECT_H
#define TRIANGLEDERIVINGFADEEFFECT_H

#include "abstractscene.h"
#include "shaders.h"

#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_3_2_Core;
class QOpenGLDebugLogger;

class TriangleDerivingFadeEffect : public AbstractScene
{
    Q_OBJECT

public:
    TriangleDerivingFadeEffect(QObject* parent = 0);
    virtual ~TriangleDerivingFadeEffect();

    virtual void initialize();
    virtual void update(float t);
    virtual void render(double currentTime);
    virtual void resize(int width, int height);

public slots:
    void onMessageLogged(QOpenGLDebugMessage message);

private:
    void prepareShaders();

    QOpenGLVertexArrayObject  * m_vao;
    QOpenGLFunctions_3_2_Core * m_funcs;
    QOpenGLDebugLogger        * m_logger;

    ShadersPtr m_shader;
};

#endif // TRIANGLEDERIVINGFADEEFFECT_H
