#ifndef TRIANGLEDERIVINGFRAGCOLOR_H
#define TRIANGLEDERIVINGFRAGCOLOR_H

#include "abstractscene.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_3_2_Core;
class QOpenGLDebugLogger;

class TriangleDerivingFragColor : public AbstractScene
{
    Q_OBJECT

public:
    TriangleDerivingFragColor(QObject* parent = 0);
    virtual ~TriangleDerivingFragColor();

    virtual void initialize();
    virtual void update(float t);
    virtual void render(double currentTime);
    virtual void resize(int width, int height);

public slots:
    void onMessageLogged(QOpenGLDebugMessage message);

private:
    void prepareShaderProgram();

    QOpenGLShaderProgram        m_shaderProgram;
    QOpenGLVertexArrayObject  * m_vao;
    QOpenGLFunctions_3_2_Core * m_funcs;
    QOpenGLDebugLogger        * m_logger;
};

#endif // TRIANGLEDERIVINGFRAGCOLOR_H
