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

    connect(RovMov, SIGNAL(UpdateSetWG(const MoveParm&)),this, SLOT(UpdateWidgets(const MoveParm&)));
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_D:
        RovMov->SetYawSpeed(FORWARD_DIR);
        qDebug()<<"keyD";
        break;
    case Qt::Key_A:
        RovMov->SetYawSpeed(REVERS_DIR);
         qDebug()<<"keyA";
        break;
     case Qt::Key_W:
        RovMov->SetMarchSpeed(FORWARD_DIR);
        break;
     case Qt::Key_S:
        RovMov->SetMarchSpeed(REVERS_DIR);
        break;
     case Qt::Key_Down:
        RovMov->SetDepthSpeed(FORWARD_DIR);
        break;
     case Qt::Key_Up:
        RovMov->SetDepthSpeed(REVERS_DIR);
        break;
     case Qt::Key_Q:
        RovMov->SetRollSpeed(FORWARD_DIR);
        break;
     case Qt::Key_E:
        RovMov->SetRollSpeed(REVERS_DIR);
        break;
    }
}

void ControlPanel::UpdateWidgets(const MoveParm &Move)
{
    qDebug()<<"Slot UpdateWigets "<<Move.Roll;
    ui->SetRollSlider->setValue(static_cast<int>(Move.Roll));
    ui->SetDepthSlider->setValue(static_cast<int>(Move.Depth));
    ui->SetRolLabel->setText(QString::number(Move.Roll,'f',0));
    ui->SetDepthLabel->setText(QString::number(Move.Depth,'f',0));
    ui->SetYawlabel->setText(QString::number(Move.Yaw,'f',0));

    txtCurrentYaw->setPlainText(QString::number(Move.Yaw));
    picROV->setRotation(Move.Yaw);

    qDebug()<<"Set Yaw: "<<Move.Yaw;
    qDebug()<<"Set Roll: "<<Move.Roll;
    qDebug()<<"Set Depth: "<<Move.Depth;
    qDebug()<<"Set March Seed: "<<Move.MarchSpeed;
}
