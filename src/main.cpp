#include "../include/point_plotter/pointplot.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    PointPlot point_plot_window(argc, argv);
    point_plot_window.show();

    return application.exec();
}
