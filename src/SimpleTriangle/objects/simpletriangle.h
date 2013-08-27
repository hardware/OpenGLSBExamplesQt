#ifndef SIMPLETRIANGLE_H
#define SIMPLETRIANGLE_H

#include "abstractscene.h"
#include "shaders.h"

#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_3_2_Core;
class QOpenGLDebugLogger;

class SimpleTriangle : public AbstractScene
{
    Q_OBJECT

public:
    SimpleTriangle(QObject* parent = 0);
    virtual ~SimpleTriangle();

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

#endif // SIMPLETRIANGLE_H
