#include "../include/point_plotter/pointplot.h"
#include "../include/point_plotter/mapviewer.h"
#include "ui_pointplot.h"

PointPlot::PointPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointPlot)
{
    ui->setupUi(this);
    QString map_path = ":/maps/random_wall/random_wall_map.pgm";
    ui->mapBox->display_map(map_path);


}

PointPlot::~PointPlot()
{
    delete ui;
}
