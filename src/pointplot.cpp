#include "../include/point_plotter/pointplot.h"
#include "../include/point_plotter/mapviewer.h"



PointPlot::PointPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointPlot)
{
    ui->setupUi(this);
	setWindowIcon(QIcon(":/images/icon.png"));
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

  //Configure selection of file, assumes image and yaml file are named similarly
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

  //Set the name of the file on the label
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
    ui->mapBox->drawDiscretisePath();
  }
  //TODO throw alert box not enough points
  return;
}

/**
 * @brief PointPlot::on_clearPointButton_clicked
 * Remove points that is currently plotted
 */
void PointPlot::on_clearPointButton_clicked()
{
  ui->mapBox->display_map(map_path);
  ui->mapBox->_pointsDrawn.clear();
  ui->mapBox->drawnPath.clear();
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


