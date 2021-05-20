#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include "rovorient.h"
#include "rovcontrol.h"
#include "datatypes.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();

public slots:
    void UpdateSetWidgets(const MoveParm &Move);
    void UpdateRovWidgets(const QVector<double> &Move);

signals:
    void KeyPressure(QKeyEvent *ev);
protected:
    void virtual keyPressEvent(QKeyEvent * e);

private slots:

    void on_ApplyButton_clicked();

    void on_SetModeButton_clicked();

    void on_DirectModeButton_clicked();

    void on_StabModeButton_clicked();

    void on_YawCheckBox_toggled(bool checked);

    void on_RollCheckBox_2_toggled(bool checked);

    void on_DepthCheckBox_toggled(bool checked);

private:
    Ui::ControlPanel *ui;

    QGraphicsScene *scene;
    QGraphicsPixmapItem *picROV;
    QGraphicsPixmapItem *picDial;
    QGraphicsTextItem *txtCurrentYaw;
    RovOrient *RovMov;
    RovControl *RovSU;
    bool SetFlag;
    bool DirectFlag;
    bool StabFlag;
};

#endif // CONTROLPANEL_H
