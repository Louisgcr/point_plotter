#include "../include/point_plotter/mapviewer.h"

mapviewer::mapviewer(QWidget *parent) :
                     QGraphicsView(parent),
                     _pointsDrawn(0, Cornu::NOT_CIRCULAR)
{
  setMouseTracking(true);
}


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

void mapviewer::get_map_resolution(const QString map_info_path){
     YAML::Node config = YAML::LoadFile(map_info_path.toStdString());
     std::string resolution_str = config["resolution"].as<std::string>();
     resolution = ::atof(resolution_str.c_str());
}

void mapviewer::drawDiscretisePath(void){

  _pointsDrawn.insert(_pointsDrawn.begin(), Eigen::Vector2d(origin_x, origin_y));
  fitter.setParams(params);
  fitter.setOriginalSketch(new Cornu::Polyline(_pointsDrawn));
  fitter.run();
  Cornu::PrimitiveSequenceConstPtr output = fitter.finalOutput();

  if(output){

     double length;
     for (int i =0; i < output->primitives().size(); i++){
         Cornu::CurveConstPtr curve = output->primitives()[i];
         for(double s = 0; s < curve->length(); s+=0.2){
             Eigen::Vector2d pt, der, der2;
             curve->eval(s, &pt, &der, &der2);
             double yaw = atan2(der[1], der[0]);
             drawnPath << QPointF(pt[0], pt[1]);
         }
     }

     for(int j =0; j < drawnPath.size()-1; j++){
       QLineF tempLine(drawnPath[j], drawnPath[j+1]);
       scene->addLine(tempLine,
                      QPen(Qt::green, 1, Qt::DashLine,Qt::RoundCap, Qt::RoundJoin));
     }
  }

}


void mapviewer::mouseDoubleClickEvent(QMouseEvent* event){

  if(event->button() == Qt::LeftButton){
    QPointF pt = mapToScene(event->pos());
    double rad = 2.5;
    scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
                      QPen(Qt::green), QBrush(Qt::green, Qt::SolidPattern));

    _pointsDrawn.push_back(Eigen::Vector2d(pt.x(), pt.y()));
    event->accept();
    return;
  }
}

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

