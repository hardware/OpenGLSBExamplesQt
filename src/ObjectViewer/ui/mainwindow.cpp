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
    resize(1366, 768);
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
    // ############ DOCK LEFT ############

    m_dockCoordinateArea = new QDockWidget("CARTESIAN COORDINATES", this);
    addDockWidget(Qt::LeftDockWidgetArea, m_dockCoordinateArea);

    m_coordinate = new QWidget;
    m_dockCoordinateArea->setWidget(m_coordinate);

    // ############ OBJECT COORDINATE GROUPBOX ############

    QLabel* objectPositionLabel = new QLabel("Position");
    QLabel* objectRotationLabel = new QLabel("Rotation");
    QLabel* objectScaleLabel    = new QLabel("Scale");

    // POSITION
    QLabel* objectPositionXLabel = new QLabel("X");
    QLabel* objectPositionYLabel = new QLabel("Y");
    QLabel* objectPositionZLabel = new QLabel("Z");

    QDoubleSpinBox* objectPositionXValue = new QDoubleSpinBox;
    QDoubleSpinBox* objectPositionYValue = new QDoubleSpinBox;
    QDoubleSpinBox* objectPositionZValue = new QDoubleSpinBox;

    QHBoxLayout* objectPositionLayout = new QHBoxLayout;
    objectPositionLayout->addWidget(objectPositionXLabel);
    objectPositionLayout->addWidget(objectPositionXValue);
    objectPositionLayout->addWidget(objectPositionYLabel);
    objectPositionLayout->addWidget(objectPositionYValue);
    objectPositionLayout->addWidget(objectPositionZLabel);
    objectPositionLayout->addWidget(objectPositionZValue);

    QWidget* objectPositionCoordinate = new QWidget;
    objectPositionCoordinate->setLayout(objectPositionLayout);

    // ROTATION
    QLabel* objectRotationXLabel = new QLabel("X");
    QLabel* objectRotationYLabel = new QLabel("Y");
    QLabel* objectRotationZLabel = new QLabel("Z");

    QDoubleSpinBox* objectRotationXValue = new QDoubleSpinBox;
    QDoubleSpinBox* objectRotationYValue = new QDoubleSpinBox;
    QDoubleSpinBox* objectRotationZValue = new QDoubleSpinBox;

    QHBoxLayout* objectRotationLayout = new QHBoxLayout;
    objectRotationLayout->addWidget(objectRotationXLabel);
    objectRotationLayout->addWidget(objectRotationXValue);
    objectRotationLayout->addWidget(objectRotationYLabel);
    objectRotationLayout->addWidget(objectRotationYValue);
    objectRotationLayout->addWidget(objectRotationZLabel);
    objectRotationLayout->addWidget(objectRotationZValue);

    QWidget* objectRotationCoordinate = new QWidget;
    objectRotationCoordinate->setLayout(objectRotationLayout);

    // SCALE
    QLabel* objectScaleXLabel = new QLabel("X");
    QLabel* objectScaleYLabel = new QLabel("Y");
    QLabel* objectScaleZLabel = new QLabel("Z");

    QDoubleSpinBox* objectScaleXValue = new QDoubleSpinBox;
    QDoubleSpinBox* objectScaleYValue = new QDoubleSpinBox;
    QDoubleSpinBox* objectScaleZValue = new QDoubleSpinBox;

    QHBoxLayout* objectScaleLayout = new QHBoxLayout;
    objectScaleLayout->addWidget(objectScaleXLabel);
    objectScaleLayout->addWidget(objectScaleXValue);
    objectScaleLayout->addWidget(objectScaleYLabel);
    objectScaleLayout->addWidget(objectScaleYValue);
    objectScaleLayout->addWidget(objectScaleZLabel);
    objectScaleLayout->addWidget(objectScaleZValue);

    QWidget* objectScaleCoordinate = new QWidget;
    objectScaleCoordinate->setLayout(objectScaleLayout);

    QGridLayout* objectCoordinateLayout = new QGridLayout;
    objectCoordinateLayout->addWidget(objectPositionLabel, 0, 0);
    objectCoordinateLayout->addWidget(objectPositionCoordinate, 0, 1);
    objectCoordinateLayout->addWidget(objectRotationLabel, 1, 0);
    objectCoordinateLayout->addWidget(objectRotationCoordinate, 1, 1);
    objectCoordinateLayout->addWidget(objectScaleLabel, 2, 0);
    objectCoordinateLayout->addWidget(objectScaleCoordinate, 2, 1);

    QGroupBox* objectCoordinateGroupBox = new QGroupBox("OBJECT");
    objectCoordinateGroupBox->setLayout(objectCoordinateLayout);

    // ############ CAMERA COORDINATE GROUPBOX ############

    QLabel* cameraPositionLabel = new QLabel("Position");
    QLabel* cameraRotationLabel = new QLabel("upVector");
    QLabel* cameraScaleLabel    = new QLabel("viewCenter");

    // POSITION
    QLabel* cameraPositionXLabel = new QLabel("X");
    QLabel* cameraPositionYLabel = new QLabel("Y");
    QLabel* cameraPositionZLabel = new QLabel("Z");

    QDoubleSpinBox* cameraPositionXValue = new QDoubleSpinBox;
    QDoubleSpinBox* cameraPositionYValue = new QDoubleSpinBox;
    QDoubleSpinBox* cameraPositionZValue = new QDoubleSpinBox;

    QHBoxLayout* cameraPositionLayout = new QHBoxLayout;
    cameraPositionLayout->addWidget(cameraPositionXLabel);
    cameraPositionLayout->addWidget(cameraPositionXValue);
    cameraPositionLayout->addWidget(cameraPositionYLabel);
    cameraPositionLayout->addWidget(cameraPositionYValue);
    cameraPositionLayout->addWidget(cameraPositionZLabel);
    cameraPositionLayout->addWidget(cameraPositionZValue);

    QWidget* cameraPositionCoordinate = new QWidget;
    cameraPositionCoordinate->setLayout(cameraPositionLayout);

    // ROTATION
    QLabel* cameraRotationXLabel = new QLabel("X");
    QLabel* cameraRotationYLabel = new QLabel("Y");
    QLabel* cameraRotationZLabel = new QLabel("Z");

    QDoubleSpinBox* cameraRotationXValue = new QDoubleSpinBox;
    QDoubleSpinBox* cameraRotationYValue = new QDoubleSpinBox;
    QDoubleSpinBox* cameraRotationZValue = new QDoubleSpinBox;

    QHBoxLayout* cameraRotationLayout = new QHBoxLayout;
    cameraRotationLayout->addWidget(cameraRotationXLabel);
    cameraRotationLayout->addWidget(cameraRotationXValue);
    cameraRotationLayout->addWidget(cameraRotationYLabel);
    cameraRotationLayout->addWidget(cameraRotationYValue);
    cameraRotationLayout->addWidget(cameraRotationZLabel);
    cameraRotationLayout->addWidget(cameraRotationZValue);

    QWidget* cameraRotationCoordinate = new QWidget;
    cameraRotationCoordinate->setLayout(cameraRotationLayout);

    // SCALE
    QLabel* cameraScaleXLabel = new QLabel("X");
    QLabel* cameraScaleYLabel = new QLabel("Y");
    QLabel* cameraScaleZLabel = new QLabel("Z");

    QDoubleSpinBox* cameraScaleXValue = new QDoubleSpinBox;
    QDoubleSpinBox* cameraScaleYValue = new QDoubleSpinBox;
    QDoubleSpinBox* cameraScaleZValue = new QDoubleSpinBox;

    QHBoxLayout* cameraScaleLayout = new QHBoxLayout;
    cameraScaleLayout->addWidget(cameraScaleXLabel);
    cameraScaleLayout->addWidget(cameraScaleXValue);
    cameraScaleLayout->addWidget(cameraScaleYLabel);
    cameraScaleLayout->addWidget(cameraScaleYValue);
    cameraScaleLayout->addWidget(cameraScaleZLabel);
    cameraScaleLayout->addWidget(cameraScaleZValue);

    QWidget* cameraScaleCoordinate = new QWidget;
    cameraScaleCoordinate->setLayout(cameraScaleLayout);

    QGridLayout* cameraCoordinateLayout = new QGridLayout;
    cameraCoordinateLayout->addWidget(cameraPositionLabel, 0, 0);
    cameraCoordinateLayout->addWidget(cameraPositionCoordinate, 0, 1);
    cameraCoordinateLayout->addWidget(cameraRotationLabel, 1, 0);
    cameraCoordinateLayout->addWidget(cameraRotationCoordinate, 1, 1);
    cameraCoordinateLayout->addWidget(cameraScaleLabel, 2, 0);
    cameraCoordinateLayout->addWidget(cameraScaleCoordinate, 2, 1);

    QGroupBox* cameraCoordinateGroupBox = new QGroupBox("CAMERA");
    cameraCoordinateGroupBox->setLayout(cameraCoordinateLayout);

    QVBoxLayout* coordinateLayout = new QVBoxLayout;
    coordinateLayout->addWidget(objectCoordinateGroupBox);
    coordinateLayout->addWidget(cameraCoordinateGroupBox);
    coordinateLayout->addStretch();

    m_coordinate->setLayout(coordinateLayout);

    // ############ DOCK RIGHT ############

    m_dockParamsArea = new QDockWidget("PARAMETERS", this);
    addDockWidget(Qt::RightDockWidgetArea, m_dockParamsArea);

    m_params = new QWidget;
    m_dockParamsArea->setWidget(m_params);

    QTabWidget* tab = new QTabWidget;

    QWidget* objectTab  = new QWidget;
    QWidget* optionsTab = new QWidget;

    tab->addTab(optionsTab, "Options");
    tab->addTab(objectTab, "Object");

    QVBoxLayout* paramsLayout = new QVBoxLayout;
    paramsLayout->addWidget(tab);
    paramsLayout->addStretch();

    m_params->setLayout(paramsLayout);

    // ############ OPTION TAB ############

    QCheckBox* animate = new QCheckBox("Animate");

    // ############ OPTION TAB - RENDERING MODE GROUPBOX ############

    QRadioButton* fill = new QRadioButton("fill");
    QRadioButton* wireframe = new QRadioButton("wireframe");
    QRadioButton* points = new QRadioButton("points");

    fill->setChecked(true);

    QVBoxLayout* renderingModeLayout = new QVBoxLayout;
    renderingModeLayout->addWidget(fill);
    renderingModeLayout->addWidget(wireframe);
    renderingModeLayout->addWidget(points);

    QGroupBox* renderingModeGroupBox = new QGroupBox("Rendering mode");
    renderingModeGroupBox->setLayout(renderingModeLayout);

    // ############ OPTION TAB - PROJECTION TYPE GROUPBOX ############

    QRadioButton* perspective = new QRadioButton("perspective");
    QRadioButton* orthographic = new QRadioButton("orthographic");

    perspective->setChecked(true);

    QVBoxLayout* projectionTypeLayout = new QVBoxLayout;
    projectionTypeLayout->addWidget(perspective);
    projectionTypeLayout->addWidget(orthographic);

    QGroupBox* projectionTypeGroupBox = new QGroupBox("Projection Type");
    projectionTypeGroupBox->setLayout(projectionTypeLayout);

    // ############ OPTION TAB - CAMERA GROUPBOX ############

    QPushButton* resetCamera = new QPushButton("Reset camera");

    QHBoxLayout* cameraLayout = new QHBoxLayout;
    cameraLayout->addWidget(resetCamera);

    QGroupBox* cameraGroupBox = new QGroupBox("CAMERA");
    cameraGroupBox->setLayout(cameraLayout);

    //############ OBJECT TAB - TRANSLATION GROUPBOX ############

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

    // ############ OBJECT TAB - ROTATION GROUPBOX ############

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

    QVBoxLayout* optionsTabLayout = new QVBoxLayout;
    optionsTabLayout->addWidget(renderingModeGroupBox);
    optionsTabLayout->addWidget(projectionTypeGroupBox);
    optionsTabLayout->addWidget(cameraGroupBox);
    optionsTabLayout->addWidget(animate, 0, Qt::AlignHCenter);
    optionsTabLayout->addStretch();

    optionsTab->setLayout(optionsTabLayout);

    QVBoxLayout* objectTabLayout = new QVBoxLayout;
    objectTabLayout->addWidget(translationGroupBox);
    objectTabLayout->addWidget(rotationGroupBox);
    objectTabLayout->addStretch();

    objectTab->setLayout(objectTabLayout);

    // ############ SIGNALS/SLOTS ############

    ObjectViewer* scene = m_openglArea->getScene();
    Object3D* object3D = scene->getObject();
    Camera* camera = scene->getCamera();

    QObject::connect(animate, SIGNAL(stateChanged(int)), m_openglArea.data(), SLOT(checkAnimate(int)));

    QObject::connect(fill,      SIGNAL(toggled(bool)), scene, SLOT(toggleFill(bool)));
    QObject::connect(wireframe, SIGNAL(toggled(bool)), scene, SLOT(toggleWireframe(bool)));
    QObject::connect(points,    SIGNAL(toggled(bool)), scene, SLOT(togglePoints(bool)));

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
