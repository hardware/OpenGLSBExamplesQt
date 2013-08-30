#include "mainwindow.h"
#include "window.h"

#include <QtWidgets>
#include <QCoreApplication>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_openglArea = new Window;
    setCentralWidget(QWidget::createWindowContainer(m_openglArea));

    initializeParamsArea();
    resize(1024, 600);
}

void MainWindow::initializeParamsArea()
{
    m_dockArea = new QDockWidget("PARAMETRES", this);
    addDockWidget(Qt::RightDockWidgetArea, m_dockArea);

    m_params = new QWidget;
    m_dockArea->setWidget(m_params);

    // OPTIONS GROUPBOX
    QCheckBox* animate = new QCheckBox("Animate");
    QCheckBox* wireframe = new QCheckBox("wireframe");

    QHBoxLayout* optionsLayout = new QHBoxLayout;
    optionsLayout->addWidget(animate);
    optionsLayout->addWidget(wireframe);

    QGroupBox* optionsGroupBox = new QGroupBox("OPTIONS");
    optionsGroupBox->setLayout(optionsLayout);

    // TRANSLATION GROUPBOX
    QSlider* translationX = new QSlider(Qt::Horizontal);
    QSlider* translationY = new QSlider(Qt::Horizontal);
    QSlider* translationZ = new QSlider(Qt::Horizontal);

    QLabel* translationXLabel = new QLabel("X");
    QLabel* translationYLabel = new QLabel("Y");
    QLabel* translationZLabel = new QLabel("Z");

    translationX->setRange(-1000, 100);
    translationX->setValue(0);
    translationY->setRange(-140, 90);
    translationY->setValue(0);
    translationZ->setRange(-150, 150);
    translationZ->setValue(0);

    QHBoxLayout* translationXLayout = new QHBoxLayout;
    translationXLayout->addWidget(translationXLabel);
    translationXLayout->addWidget(translationX);

    QHBoxLayout* translationYLayout = new QHBoxLayout;
    translationYLayout->addWidget(translationYLabel);
    translationYLayout->addWidget(translationY);

    QHBoxLayout* translationZLayout = new QHBoxLayout;
    translationZLayout->addWidget(translationZLabel);
    translationZLayout->addWidget(translationZ);

    QVBoxLayout* translationLayout = new QVBoxLayout;
    translationLayout->addLayout(translationXLayout);
    translationLayout->addLayout(translationYLayout);
    translationLayout->addLayout(translationZLayout);

    QGroupBox* translationGroupBox = new QGroupBox("TRANSLATION");
    translationGroupBox->setLayout(translationLayout);

    // ROTATION GROUPBOX
    QDial* rotationX = new QDial;
    QDial* rotationY = new QDial;
    QDial* rotationZ = new QDial;

    QLabel* rotationXLabel = new QLabel("X");
    QLabel* rotationYLabel = new QLabel("Y");
    QLabel* rotationZLabel = new QLabel("Z");

    rotationX->setRange(0, 360);
    rotationX->setValue(0);
    rotationY->setRange(0, 360);
    rotationY->setValue(0);
    rotationZ->setRange(0, 360);
    rotationZ->setValue(0);

    rotationXLabel->setAlignment(Qt::AlignCenter);
    rotationYLabel->setAlignment(Qt::AlignCenter);
    rotationZLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* rotationLayout = new QVBoxLayout;
    rotationLayout->addWidget(rotationXLabel);
    rotationLayout->addWidget(rotationX);
    rotationLayout->addWidget(rotationYLabel);
    rotationLayout->addWidget(rotationY);
    rotationLayout->addWidget(rotationZLabel);
    rotationLayout->addWidget(rotationZ);

    QGroupBox* rotationGroupBox = new QGroupBox("ROTATION");
    rotationGroupBox->setLayout(rotationLayout);

    QVBoxLayout* dockLayout = new QVBoxLayout;
    dockLayout->addWidget(optionsGroupBox);
    dockLayout->addWidget(translationGroupBox);
    dockLayout->addWidget(rotationGroupBox);
    dockLayout->addStretch();

    m_params->setLayout(dockLayout);

    QObject::connect(animate, SIGNAL(stateChanged(int)), m_openglArea, SLOT(checkAnimate(int)));
    QObject::connect(wireframe, SIGNAL(stateChanged(int)), m_openglArea, SLOT(checkWireframe(int)));

    QObject::connect(translationX, SIGNAL(valueChanged(int)), m_openglArea, SLOT(setObjectXPosition(int)));
    QObject::connect(translationY, SIGNAL(valueChanged(int)), m_openglArea, SLOT(setObjectYPosition(int)));
    QObject::connect(translationZ, SIGNAL(valueChanged(int)), m_openglArea, SLOT(setObjectZPosition(int)));

    QObject::connect(rotationX, SIGNAL(valueChanged(int)), m_openglArea, SLOT(setObjectXRotation(int)));
    QObject::connect(rotationY, SIGNAL(valueChanged(int)), m_openglArea, SLOT(setObjectYRotation(int)));
    QObject::connect(rotationZ, SIGNAL(valueChanged(int)), m_openglArea, SLOT(setObjectZRotation(int)));
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
    case Qt::Key_Escape:

        QCoreApplication::instance()->quit();
        break;

    default:
        QMainWindow::keyPressEvent(e);
    }
}
