#include "object3d.h"

Object3D::Object3D()
    : m_position(0.0f, 0.0f, 0.0f),
      m_rotation(0.0f, 0.0f, 0.0f),
      m_scale(1.0f, 1.0f, 1.0f)
{}

void Object3D::setPosition(const QVector3D& positionVector)
{
    m_position = positionVector;
}

void Object3D::setPosition(float x, float y, float z)
{
    m_position.setX(x);
    m_position.setY(y);
    m_position.setZ(z);
}

void Object3D::setRotation(const QVector3D& rotationVector)
{
    m_rotation = rotationVector;
}

void Object3D::setRotation(float x, float y, float z)
{
    m_rotation.setX(x);
    m_rotation.setY(y);
    m_rotation.setZ(z);
}

void Object3D::setScale(const QVector3D& scale)
{
    m_scale = scale;
}

void Object3D::setScale(float x, float y, float z)
{
    m_scale.setX(x);
    m_scale.setY(y);
    m_scale.setZ(z);
}

void Object3D::setScale(float scaleFactor)
{
    m_scale.setX(scaleFactor);
    m_scale.setY(scaleFactor);
    m_scale.setZ(scaleFactor);
}

void Object3D::translate(const QVector3D &translationVector)
{
    m_position.setX(m_position.x() + translationVector.x());
    m_position.setY(m_position.y() + translationVector.y());
    m_position.setZ(m_position.z() + translationVector.z());
}

void Object3D::translate(float x, float y, float z)
{
    m_position.setX(m_position.x() + x);
    m_position.setY(m_position.y() + y);
    m_position.setZ(m_position.z() + z);
}

void Object3D::translateX(float x)
{
    m_position.setX(m_position.x() + x);
}

void Object3D::translateY(float y)
{
    m_position.setY(m_position.y() + y);
}

void Object3D::translateZ(float z)
{
    m_position.setZ(m_position.z() + z);
}

void Object3D::rotate(const QVector3D &rotationVector)
{
    m_rotation.setX(m_rotation.x() + rotationVector.x());
    m_rotation.setY(m_rotation.y() + rotationVector.y());
    m_rotation.setZ(m_rotation.z() + rotationVector.z());
}

void Object3D::rotate(float x, float y, float z)
{
    m_rotation.setX(m_rotation.x() + x);
    m_rotation.setY(m_rotation.y() + y);
    m_rotation.setZ(m_rotation.z() + z);
}

void Object3D::rotateX(float x)
{
    m_rotation.setX(m_rotation.x() + x);
}

void Object3D::rotateY(float y)
{
    m_rotation.setY(m_rotation.y() + y);
}

void Object3D::rotateZ(float z)
{
    m_rotation.setZ(m_rotation.z() + z);
}

void Object3D::scale(const QVector3D &scaleVector)
{
    m_scale.setX(m_scale.x() + scaleVector.x());
    m_scale.setY(m_scale.y() + scaleVector.y());
    m_scale.setZ(m_scale.z() + scaleVector.z());
}

void Object3D::scale(float x, float y, float z)
{
    m_scale.setX(m_scale.x() + x);
    m_scale.setY(m_scale.y() + y);
    m_scale.setZ(m_scale.z() + z);
}

void Object3D::scale(float scaleFactor)
{
    m_scale.setX(m_scale.x() * scaleFactor);
    m_scale.setY(m_scale.y() * scaleFactor);
    m_scale.setZ(m_scale.z() * scaleFactor);
}

void Object3D::scaleX(float x)
{
    m_scale.setX(m_scale.x() + x);
}

void Object3D::scaleY(float y)
{
    m_scale.setY(m_scale.y() + y);
}

void Object3D::scaleZ(float z)
{
    m_scale.setZ(m_scale.z() + z);
}

const QVector3D& Object3D::getPosition() const
{
    return m_position;
}

const QVector3D& Object3D::getRotation() const
{
    return m_rotation;
}

const QVector3D& Object3D::getScale() const
{
    return m_scale;
}

const QMatrix4x4& Object3D::getModelMatrix()
{
    m_modelMatrix.setToIdentity();

    m_modelMatrix.translate(m_position);
    m_modelMatrix.rotate(m_rotation.x(), 1.0f, 0.0f, 0.0f);
    m_modelMatrix.rotate(m_rotation.y(), 0.0f, 1.0f, 0.0f);
    m_modelMatrix.rotate(m_rotation.z(), 0.0f, 0.0f, 1.0f);
    m_modelMatrix.scale(m_scale);

    return m_modelMatrix;
}

void Object3D::setObjectXPosition(int x)
{
    setPosition((float)x/100.0f, m_position.y(), m_position.z());
}

void Object3D::setObjectYPosition(int y)
{
    setPosition(m_position.x(), (float)y/100.0f, m_position.z());
}

void Object3D::setObjectZPosition(int z)
{
    setPosition(m_position.x(), m_position.y(), (float)z/100.0f);
}

void Object3D::setObjectXRotation(int x)
{
    setRotation((float)x, m_rotation.y(), m_rotation.z());
}

void Object3D::setObjectYRotation(int y)
{
    setRotation(m_rotation.x(), (float)y, m_rotation.z());
}

void Object3D::setObjectZRotation(int z)
{
    setRotation(m_rotation.x(), m_rotation.y(), (float)z);
}
