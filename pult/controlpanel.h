#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include "rovorient.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();

protected:
    void virtual keyPressEvent(QKeyEvent * e);

private:
    Ui::ControlPanel *ui;

    QGraphicsScene *scene;
    QGraphicsPixmapItem *picROV;
    QGraphicsPixmapItem *picDial;
    QGraphicsTextItem *txtCurrentYaw;
    RovOrient *RovMov;
};

#endif // CONTROLPANEL_H
