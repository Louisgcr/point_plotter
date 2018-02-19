#ifndef POINTPLOT_H
#define POINTPLOT_H

#include <QWidget>
#include "ui_pointplot.h"
namespace Ui {
class PointPlot;
}

class PointPlot : public QWidget
{
    Q_OBJECT

public:
    explicit PointPlot(QWidget *parent = 0);
    ~PointPlot();

private:
    Ui::PointPlot *ui;
};

#endif // POINTPLOT_H
