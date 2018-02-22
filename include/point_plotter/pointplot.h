#ifndef POINTPLOT_H
#define POINTPLOT_H

#include "pp_qros.h"
#include "ui_pointplot.h"
#include <QString>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QLayout>
#include <QSplitter>
#include <QFileDialog>

namespace Ui {
class PointPlot;
}

class PointPlot : public QWidget
{
    Q_OBJECT

public:
    explicit PointPlot(int argc, char** argv, QWidget *parent = 0);
    ~PointPlot();
    QString map_path, map_info_path;
    PP::QROS qros;

private slots:
  /**
  * @brief PointPlot::on_fileDir_clicked
  * When clicked, it opens file directory to choose image to display on mapbox
  */
  void on_fileDir_clicked();
  /**
  * @brief PointPlot::on_plotPointButton_clicked
  * When clicked, it plots the point and the corresponding bezier curve of the path
  */
  void on_plotPointButton_clicked();
  /**
  * @brief PointPlot::on_clearPointButton_clicked
  * Remove points that is currently plotted
  */
  void on_clearPointButton_clicked();
  /**
  * @brief PointPlot::on_runButton_clicked
  * Ask ROS to execute the program to run the path planner
  */
  void on_runButton_clicked();
  /**
  * @brief PointPlot::on_stopButton_clicked
  * Ask ROS to stop the car
  */
  void on_stopButton_clicked();
  /**
  * @brief PointPlot::on_quitButton_clicked
  * Quit the program
  */
  void on_quitButton_clicked();
  /**
  * @brief PointPlot::Display no master on info box
  * Display no master on info box
  */
  void displayNoMaster();

private:
    Ui::PointPlot *ui;
};

#endif // POINTPLOT_H
