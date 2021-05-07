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
    void UpdateRovWidgets(const MoveParm &Move);

signals:
    void KeyPressure(QKeyEvent *ev);
protected:
    void virtual keyPressEvent(QKeyEvent * e);

private:
    Ui::ControlPanel *ui;

    QGraphicsScene *scene;
    QGraphicsPixmapItem *picROV;
    QGraphicsPixmapItem *picDial;
    QGraphicsTextItem *txtCurrentYaw;
    RovOrient *RovMov;
    RovControl *RovSU;
};

#endif // CONTROLPANEL_H
