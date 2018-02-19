#include "../include/point_plotter/mapviewer.h"

mapviewer::mapviewer(QWidget *parent) : QGraphicsView(parent)//: QWidget(parent)
{
  setMouseTracking(true);
}


void mapviewer::mousePressEvent(QMouseEvent* event)
{
  qDebug() << event->pos();
}

void mapviewer::display_map(const QString map_path){

  QGraphicsScene *scene =  new QGraphicsScene;
  QPixmap image(map_path);
  scene->addPixmap(image);
  setScene(scene);
  show();

}
