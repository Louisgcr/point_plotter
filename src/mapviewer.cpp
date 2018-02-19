#include "../include/point_plotter/mapviewer.h"
#include <iostream>
#include <stdio.h>
#include <yaml-cpp/yaml.h>

mapviewer::mapviewer(QWidget *parent) : QGraphicsView(parent)//: QWidget(parent)
{
  setMouseTracking(true);
  setDragMode(ScrollHandDrag);

}

/**
 * @brief mousePressEvent: Gets the position of mouse relative to the widget
 * @param event: Click event
 */
void mapviewer::mousePressEvent(QMouseEvent* event)
{

  if(event->button() == Qt::RightButton){
    QPointF pt = mapToScene(event->pos());
    double rad = 2.5;
    scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
                      QPen(Qt::green), QBrush(Qt::green, Qt::SolidPattern));
  }
}

/**
 * @brief display_map: Creates a scence and a pixmap to display
 * @param map_path: Path to image file
 */
void mapviewer::display_map(const QString map_path){

  //Set scene and display map
  image->load(map_path);
  scene->addPixmap(*image);
  setScene(scene);
  show();

  //Get infomation of map, height width and origin
  map_width = scene->width() ;
  map_height = scene->height();
  origin_x = map_width/2;
  origin_y = map_height/2;

  scene->addRect(origin_x - prius_length/(2*resolution), origin_y -prius_width/(2*resolution), prius_length/resolution, prius_width/resolution,
                 QPen(Qt::green, 1, Qt::DashLine,Qt::RoundCap, Qt::RoundJoin),
                 QBrush(Qt::green, Qt::NoBrush));

}

/**
 * @brief get_map_resolution: get resolution of map
 * @param map_info_path
 */
void mapviewer::get_map_resolution(const QString map_info_path){
     YAML::Node config = YAML::LoadFile(map_info_path.toStdString());
     std::string resolution_str = config["resolution"].as<std::string>();
     resolution = ::atof(resolution_str.c_str());
}
