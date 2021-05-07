#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QDebug>

ControlPanel::ControlPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    ui->SetDepthLabel->setText("0");
    ui->SetRolLabel->setText("0");
    ui->SetYawlabel->setText("0");
    ui->CurDepthLabel->setText("0");
    ui->CurRolLabel->setText("0");
    ui->DepthBar->setValue(0);
    ui->RollBar->setValue(0);
    ui->SetRollSlider->setValue(0);
    ui->SetDepthSlider->setValue(0);

    RovMov = new RovOrient(this);
    RovSU = new RovControl(this);

    scene = new QGraphicsScene (ui->YawView);
    ui->YawView->setScene(scene);
    ui->YawView->setStyleSheet("background: transparent");
    ui->YawView->setRenderHint(QPainter::Antialiasing);
    picDial = scene->addPixmap(QPixmap("C:\\Users\\Lenovo\\Desktop\\development\\QTsem2\\pult\\build-pult\\images\\dial.png"));
    picROV = scene->addPixmap(QPixmap("C:\\Users\\Lenovo\\Desktop\\development\\QTsem2\\pult\\build-pult\\images\\rov.png"));
    txtCurrentYaw = scene->addText(QString::number(0), QFont("Times New Roman",14));
    picROV->setTransform(QTransform::fromScale(0.5,0.5));
    picROV->setPos(picDial->pixmap().width()/2-picROV->pixmap().width()/4+4,
                   picDial->pixmap().height()/2-picROV->pixmap().height()/4-8);
    QTransform t;
    t.translate(picDial->pixmap().width()/2-10, picDial->pixmap().height()/2-14);
    txtCurrentYaw->setTransform(t);
    picROV->setTransformOriginPoint(picDial->pixmap().width()/2,picROV->pixmap().height()/2);
    picROV->setRotation(0);

    connect(RovMov, SIGNAL(UpdateSetWG(const MoveParm&)),this, SLOT(UpdateSetWidgets(const MoveParm&)));
    connect(this,SIGNAL(KeyPressure(QKeyEvent*)),RovMov,SLOT(KeyGrab(QKeyEvent*)));
    connect(this, SIGNAL(KeyPressure(QKeyEvent*)), RovSU,SLOT(key(QKeyEvent *)));
    connect(RovSU,SIGNAL(UpdateRoveWidgents(const MoveParm&)),this,SLOT(UpdateRovWidgets(const MoveParm&)));
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::keyPressEvent(QKeyEvent *e)
{
    emit KeyPressure(e);
}

void ControlPanel::UpdateSetWidgets(const MoveParm &Move)
{
    ui->SetRollSlider->setValue(static_cast<int>(Move.Roll));
    ui->SetDepthSlider->setValue(static_cast<int>(Move.Depth));
    ui->SetRolLabel->setText(QString::number(Move.Roll,'f',0));
    ui->SetDepthLabel->setText(QString::number(Move.Depth,'f',1));
    ui->SetYawlabel->setText(QString::number(Move.Yaw,'f',0));
    RovSU->SetYaw(Move);
}

void ControlPanel::UpdateRovWidgets(const MoveParm &Move)
{
    picROV->setRotation(Move.Roll);
    txtCurrentYaw->setPlainText(QString::number(Move.Yaw,'f',1));
    ui->RollBar->setValue(static_cast<int>(Move.Roll));
    ui->DepthBar->setValue(static_cast<int>(Move.Depth));
    ui->CurRolLabel->setText(QString::number(Move.Roll,'f',0));
    ui->CurDepthLabel->setText(QString::number(Move.Depth,'f',1));
}
