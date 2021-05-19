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
    picDial = scene->addPixmap(QPixmap("./dial.png"));
    picROV = scene->addPixmap(QPixmap("./rov.png"));
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
    connect(RovSU,SIGNAL(UpdateRoveWidgents(const QVector<double> &)),this,SLOT(UpdateRovWidgets(const QVector<double> &)));
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
    RovSU->SetRovParm(Move);
}

void ControlPanel::UpdateRovWidgets(const QVector<double> &Move)
{
    picROV->setRotation(Move[RovControl::Yaw]);
    txtCurrentYaw->setPlainText(QString::number(Move[RovControl::Yaw],'f',1));
    ui->RollBar->setValue(static_cast<int>(Move[RovControl::Roll]));
    ui->DepthBar->setValue(static_cast<int>(Move[RovControl::Depth]));
    ui->CurRolLabel->setText(QString::number(Move[RovControl::Roll],'f',0));
    ui->CurDepthLabel->setText(QString::number(Move[RovControl::Depth],'f',1));
}
