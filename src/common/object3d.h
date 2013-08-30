#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Object3D : public QObject
{

    Q_OBJECT

public:
    Object3D();

    void setPosition(const QVector3D& positionVector);
    void setPosition(float x, float y, float z);

    void setRotation(const QVector3D& rotationVector);
    void setRotation(float x, float y, float z);

    void setScale(const QVector3D& scale);
    void setScale(float x, float y, float z);
    void setScale(float scaleFactor);

    void translate(const QVector3D& translationVector);
    void translate(float x, float y, float z);
    void translateX(float x);
    void translateY(float y);
    void translateZ(float z);

    void rotate(const QVector3D& rotationVector);
    void rotate(float x, float y, float z);
    void rotateX(float x);
    void rotateY(float y);
    void rotateZ(float z);

    void scale(const QVector3D& scaleVector);
    void scale(float x, float y, float z);
    void scale(float scaleFactor);
    void scaleX(float x);
    void scaleY(float y);
    void scaleZ(float z);

    const QVector3D&  getPosition() const;
    const QVector3D&  getRotation() const;
    const QVector3D&  getScale() const;
    const QMatrix4x4& getModelMatrix();

public slots:
    void setObjectXPosition(int x);
    void setObjectYPosition(int y);
    void setObjectZPosition(int z);

    void setObjectXRotation(int x);
    void setObjectYRotation(int y);
    void setObjectZRotation(int z);

private:
    QVector3D m_position;
    QVector3D m_rotation;
    QVector3D m_scale;

    QMatrix4x4 m_modelMatrix;
};

#endif // OBJECT3D_H
