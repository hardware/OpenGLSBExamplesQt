﻿#ifndef MOVINGTRIANGLE_H
#define MOVINGTRIANGLE_H

#include "abstractscene.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLDebugMessage>

class QOpenGLVertexArrayObject;
class QOpenGLFunctions_4_3_Core;
class QOpenGLDebugLogger;

class MovingTriangle : public AbstractScene
{
    Q_OBJECT

public:
    MovingTriangle(QObject* parent = 0);
    virtual ~MovingTriangle();

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
    QOpenGLFunctions_4_3_Core * m_funcs;
    QOpenGLDebugLogger        * m_logger;
};

#endif // MOVINGTRIANGLE_H
