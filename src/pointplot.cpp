#include "../include/point_plotter/pointplot.h"
#include "../include/point_plotter/mapviewer.h"
#include "ui_pointplot.h"
#include <QFileSystemModel>
#include <QTreeView>
#include <QLayout>
#include <QSplitter>
#include <QFileDialog>
#include "Cornucopia.h"


PointPlot::PointPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointPlot)
{
    ui->setupUi(this);

}

PointPlot::~PointPlot()
{
    delete ui;
}

/**
 * @brief PointPlot::on_fileDir_clicked
 * When clicked, it opens file directory to choose image to display on mapbox
 */
void PointPlot::on_fileDir_clicked()
{
  QString currentDir = QDir::currentPath();
  currentDir.append("/src/point_plotter/resources/maps");
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Open File"),
                                                  currentDir,
                                                  tr("Image Files (*.pgm);; YAML files (*.yaml)"));

  if(fileName.contains(".pgm")){
    map_path = fileName;
    fileName.replace(".pgm", ".yaml");
    map_info_path = fileName;
  }else if(fileName.contains(".yaml")){
    map_info_path = fileName;
    fileName.replace(".yaml", ".pgm");
    map_path = fileName;
  }else{
    qErrnoWarning("Type of File selected is wrong");
    return;
  }

  //Get resolution of map
  ui->mapBox->get_map_resolution(map_info_path);
  ui->mapBox->display_map(map_path);

  ui->fileDirLabel->setText(map_path);
  ui->fileDirLabel->setWordWrap(true);

}

/**
 * @brief PointPlot::on_plotPointButton_clicked
 * When clicked, it plots the point and the corresponding bezier curve of the path
 */
void PointPlot::on_plotPointButton_clicked()
{
  if(ui->mapBox->_pointsDrawn.size() > 1){

       Cornu::Fitter fitter;
       Cornu::Parameters params;
       fitter.setParams(params);
       fitter.setOriginalSketch(new Cornu::Polyline(ui->mapBox->_pointsDrawn));
       Cornu::PrimitiveSequenceConstPtr output = fitter.finalOutput();
       //std::cout<<output->primitives().size()<<std::endl;
       //std::cout<<output->primitives().toLinearIdx(0);


    return;
  }
}

/**
 * @brief PointPlot::on_clearPointButton_clicked
 * Remove points that is currently plotted
 */
void PointPlot::on_clearPointButton_clicked()
{
  ui->mapBox->display_map(map_path);
  ui->mapBox->_pointsDrawn.clear();
}

/**
 * @brief PointPlot::on_runButton_clicked
 * Ask ROS to execute the program to run the path planner
 */
void PointPlot::on_runButton_clicked()
{

}

/**
 * @brief PointPlot::on_stopButton_clicked
 * Ask ROS to stop the car
 */
void PointPlot::on_stopButton_clicked()
{

}

/**
 * @brief PointPlot::on_quitButton_clicked
 * Quit the program
 */
void PointPlot::on_quitButton_clicked()
{

}


