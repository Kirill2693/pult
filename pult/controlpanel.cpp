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

    SetFlag = false;
    DirectFlag = true;
    StabFlag = false;

    ui->YawCheckBox->setEnabled(false);
    ui->DepthCheckBox->setEnabled(false);
    ui->RollCheckBox_2->setEnabled(false);

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



void ControlPanel::on_ApplyButton_clicked()
{
    if(SetFlag == true)
    {
    int contour = ui->ContourBox->currentIndex();
    switch (contour)
    {
    case RovControl::Yaw:
        RovSU->SetK1(RovControl::Yaw,ui->K1SpinBox->value());
        RovSU->SetK2(RovControl::Yaw,ui->K2SpinBox->value());
        RovSU->SetKsp(RovControl::Yaw,ui->K3SpinBox->value());
        RovSU->SetKosPos(RovControl::Yaw,ui->KosPosSpinBox->value());
        break;
    case RovControl::Roll:
        RovSU->SetK1(RovControl::Roll,ui->K1SpinBox->value());
        RovSU->SetK2(RovControl::Roll,ui->K2SpinBox->value());
        RovSU->SetKsp(RovControl::Roll,ui->K3SpinBox->value());
        RovSU->SetKosPos(RovControl::Roll,ui->KosPosSpinBox->value());
        break;
     case RovControl::Depth:
        RovSU->SetK1(RovControl::Depth,ui->K1SpinBox->value());
        RovSU->SetK2(RovControl::Depth,ui->K2SpinBox->value());
        RovSU->SetKsp(RovControl::Depth,ui->K3SpinBox->value());
        RovSU->SetKosPos(RovControl::Depth,ui->KosPosSpinBox->value());
        break;
    }
    }
}

void ControlPanel::on_SetModeButton_clicked()
{
    SetFlag = true;
    StabFlag = false;
    DirectFlag = false;
    ui->WorkModelabel->setText("Настройка");
    RovSU->SetMode(RovControl::Yaw, RovControl::SettingsMode);
    RovSU->SetMode(RovControl::Roll, RovControl::SettingsMode);
    RovSU->SetMode(RovControl::Depth, RovControl::SettingsMode);
    ui->YawCheckBox->setEnabled(false);
    ui->DepthCheckBox->setEnabled(false);
    ui->RollCheckBox_2->setEnabled(false);
}


void ControlPanel::on_DirectModeButton_clicked()
{
    SetFlag = false;
    StabFlag = false;
    DirectFlag = true;
    ui->WorkModelabel->setText("Ручной");
    RovSU->SetMode(RovControl::Yaw, RovControl::DirectMode);
    RovSU->SetMode(RovControl::Roll, RovControl::DirectMode);
    RovSU->SetMode(RovControl::Depth, RovControl::DirectMode);
    ui->YawCheckBox->setEnabled(false);
    ui->DepthCheckBox->setEnabled(false);
    ui->RollCheckBox_2->setEnabled(false);
}

void ControlPanel::on_StabModeButton_clicked()
{
    ui->YawCheckBox->setEnabled(true);
    ui->DepthCheckBox->setEnabled(true);
    ui->RollCheckBox_2->setEnabled(true);
    SetFlag = false;
    StabFlag = true;
    DirectFlag = false;
    ui->WorkModelabel->setText("Стабилизация");
    RovSU->SetMode(RovControl::Yaw, RovControl::DirectMode);
    RovSU->SetMode(RovControl::Roll, RovControl::DirectMode);
    RovSU->SetMode(RovControl::Depth, RovControl::DirectMode);
    if(ui->YawCheckBox->isChecked())
    {
        RovSU->SetMode(RovControl::Yaw, RovControl::StabMode);
    }
    if(ui->RollCheckBox_2->isChecked())
    {
        RovSU->SetMode(RovControl::Roll, RovControl::StabMode);
    }
    if(ui->DepthCheckBox->isChecked())
    {
        RovSU->SetMode(RovControl::Depth, RovControl::StabMode);
    }
}



void ControlPanel::on_YawCheckBox_toggled(bool checked)
{
    if(checked)
    {
        RovSU->SetMode(RovControl::Yaw, RovControl::StabMode);
    }
    else
    {
        RovSU->SetMode(RovControl::Yaw, RovControl::DirectMode);
    }
}

void ControlPanel::on_RollCheckBox_2_toggled(bool checked)
{
    if(checked)
    {
        RovSU->SetMode(RovControl::Roll, RovControl::StabMode);
    }
    else
    {
        RovSU->SetMode(RovControl::Roll, RovControl::DirectMode);
    }
}

void ControlPanel::on_DepthCheckBox_toggled(bool checked)
{
    if(checked)
    {
        RovSU->SetMode(RovControl::Depth, RovControl::StabMode);
    }
    else
    {
        RovSU->SetMode(RovControl::Depth, RovControl::DirectMode);
    }
}
