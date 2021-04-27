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

    RovMov = new RovOrient(this);
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
     case Qt::Key_Control:
        RovMov->SetRollSpeed(FORWARD_DIR);
        break;
     case Qt::Key_Alt:
        RovMov->SetRollSpeed(REVERS_DIR);
        break;
    }
}
