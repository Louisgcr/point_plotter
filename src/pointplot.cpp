#include "../include/point_plotter/pointplot.h"
#include "../include/point_plotter/mapviewer.h"



PointPlot::PointPlot(int argc, char** argv, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointPlot),
    qros(argc, argv)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/icon.png"));

    //When ROS shutdown, quit the UI
    QObject::connect(&qros, SIGNAL(rosShutdown()), this, SLOT(on_quitButton_clicked()));
    QObject::connect(&qros, SIGNAL(noROSMaster()), this, SLOT(displayNoMaster()));

}

PointPlot::~PointPlot()
{
    delete ui;
}

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


void PointPlot::on_plotPointButton_clicked()
{
  if(ui->mapBox->_pointsDrawn.size() > 1){
    ui->mapBox->drawDiscretisePath();
  }
  //TODO throw alert box not enough points
  return;
}


void PointPlot::on_clearPointButton_clicked()
{
  ui->mapBox->display_map(map_path);
  ui->mapBox->_pointsDrawn.clear();
  ui->mapBox->drawnPath.clear();
}


void PointPlot::on_runButton_clicked()
{

  if(! ros::master::check()){
    qros.init();
    return;
  }

}


void PointPlot::on_stopButton_clicked()
{

}


void PointPlot::on_quitButton_clicked()
{
  close();
}

void PointPlot::displayNoMaster(){
  QString noMaster = "No ROS Master found...\n";
  ui->infoBox->insertPlainText(noMaster);
  ui->infoBox->verticalScrollBar()->setValue(ui->infoBox->verticalScrollBar()->maximum());

}

