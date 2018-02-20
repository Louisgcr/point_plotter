#include "../include/point_plotter/mapviewer.h"


mapviewer::mapviewer(QWidget *parent) : QGraphicsView(parent)//: QWidget(parent)
{
  setMouseTracking(true);
}

/**
 * @brief mouseDoubleClickEvent: Double left click to add points to the map and to the array
 * @param event
 */
void mapviewer::mouseDoubleClickEvent(QMouseEvent* event){

  if(event->button() == Qt::LeftButton){
    QPointF pt = mapToScene(event->pos());
    double rad = 2.5;
    scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
                      QPen(Qt::green), QBrush(Qt::green, Qt::SolidPattern));
    event->accept();
    return;
  }
}
/**
 * @brief mousePressEvent: Left click or middle wheel button click to start panning
 * @param event: Click event
 */
void mapviewer::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton)
  {
      _pan = true;
      _panStartX = event->x();
      _panStartY = event->y();
      setCursor(Qt::ClosedHandCursor);
      event->accept();
      return;
  }
}
/**
 * @brief mouseReleaseEvent: release left button or middle button to stop panning
 * @param event
 */
void mapviewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton)
    {
        _pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();
}

/**
 * @brief mouseMoveEvent: Store mouse position relative to the scene for zooming case
 *                        Set horizontal and vertical scroll bars for panning
 * @param event
 */
void mapviewer::mouseMoveEvent(QMouseEvent* event)
{
  target_viewport_pos = event->pos();
  target_scene_pos = mapToScene(event->pos());

  if (_pan)
  {
      horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStartX));
      verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStartY));
      _panStartX = event->x();
      _panStartY = event->y();
      event->accept();
      return;
  }
  event->ignore();
}

/**
 * @brief wheelEvent: rescale the image to zoom and unzoom, set view area to where the mouse is
 * @param event
 */
void mapviewer::wheelEvent(QWheelEvent *event){
        // Scale the view / do the zoom
        double scaleFactor = 1.15;
        if(event->delta() > 0) {
            // Zoom in
            scale(scaleFactor, scaleFactor);

        } else {
            // Zooming out
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }


        QPointF delta_viewport_pos = target_viewport_pos - QPointF(viewport()->width() / 2.0,
                                                                     viewport()->height() / 2.0);
        QPointF viewport_center = mapFromScene(target_scene_pos) - delta_viewport_pos;
        centerOn(mapToScene(viewport_center.toPoint()));

        event->accept();
        return;
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
