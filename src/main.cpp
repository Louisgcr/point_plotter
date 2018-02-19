#include "../include/point_plotter/pointplot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PointPlot w;
    w.show();

    return a.exec();
}
