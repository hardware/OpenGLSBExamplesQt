#include "mainwindow.h"
#include "window.h"
#include "object3d.h"
#include "../objects/objectviewer.h"
#include "camera.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_openglArea(new Window)
{
    resize(1024, 600);
    setCentralWidget(QWidget::createWindowContainer(m_openglArea.data()));

    initializeMenuBar();
    initializeParamsArea();
}

MainWindow::~MainWindow() {}

void MainWindow::initializeMenuBar()
{
    QAction *exitAction = new QAction("&Exit", this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));

    QAction *fullscreenAction = new QAction("&Fullscreen", this);
    fullscreenAction->setCheckable(true);
    fullscreenAction->setShortcut(QKeySequence(Qt::Key_F11));

    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAction);

    QMenu *windowMenu = menuBar()->addMenu("&Window");
    windowMenu->addAction(fullscreenAction);

    QObject::connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(fullscreenAction, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
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

    // CAMERA GROUPBOX
    QPushButton* resetCamera = new QPushButton("Reset camera");

    QHBoxLayout* cameraLayout = new QHBoxLayout;
    cameraLayout->addWidget(resetCamera);

    QGroupBox* cameraGroupBox = new QGroupBox("CAMERA");
    cameraGroupBox->setLayout(cameraLayout);

    // TRANSLATION GROUPBOX
    QSlider* translationX = new QSlider(Qt::Horizontal);
    QSlider* translationY = new QSlider(Qt::Horizontal);
    QSlider* translationZ = new QSlider(Qt::Horizontal);

    QLabel* translationXLabel = new QLabel("X");
    QLabel* translationYLabel = new QLabel("Y");
    QLabel* translationZLabel = new QLabel("Z");

    translationX->setRange(-150, 150);
    translationX->setValue(0);
    translationY->setRange(-150, 150);
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
    dockLayout->addWidget(cameraGroupBox);
    dockLayout->addWidget(translationGroupBox);
    dockLayout->addWidget(rotationGroupBox);
    dockLayout->addStretch();

    m_params->setLayout(dockLayout);

    ObjectViewer* scene = m_openglArea->getScene();
    Object3D* object3D = scene->getObject();
    Camera* camera = scene->getCamera();

    QObject::connect(animate, SIGNAL(stateChanged(int)), m_openglArea.data(), SLOT(checkAnimate(int)));
    QObject::connect(wireframe, SIGNAL(stateChanged(int)), scene, SLOT(checkWireframe(int)));

    QObject::connect(resetCamera, SIGNAL(clicked()), camera, SLOT(resetCamera()));

    QObject::connect(translationX, SIGNAL(valueChanged(int)), object3D, SLOT(setObjectXPosition(int)));
    QObject::connect(translationY, SIGNAL(valueChanged(int)), object3D, SLOT(setObjectYPosition(int)));
    QObject::connect(translationZ, SIGNAL(valueChanged(int)), object3D, SLOT(setObjectZPosition(int)));

    QObject::connect(rotationX, SIGNAL(valueChanged(int)), object3D, SLOT(setObjectXRotation(int)));
    QObject::connect(rotationY, SIGNAL(valueChanged(int)), object3D, SLOT(setObjectYRotation(int)));
    QObject::connect(rotationZ, SIGNAL(valueChanged(int)), object3D, SLOT(setObjectZRotation(int)));
}

void MainWindow::setFullScreen(bool state)
{
    (state) ? showFullScreen() : showNormal();
}
