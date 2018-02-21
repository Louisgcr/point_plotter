#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QScrollBar>

#include <iostream>
#include <stdio.h>
#include <yaml-cpp/yaml.h>
#include "Cornucopia.h"
//#include <VectorC.h>
//#include <Polyline.h>

#define prius_width  1.76
#define prius_length 4.5
/**
 * @brief The mapviewer class deals with everything pertaining to the graphicscene on the
 * UI. From the loading of image, to the drawing of points and lines to the storage of points
 * to draw the map
 *
 * Library in use to draw the map is cornocopia-lib and is requried to compile the program
 */
class mapviewer : public QGraphicsView
{
  Q_OBJECT
public:
  /**
   * @brief mapviewer constructor
   * @param parent
   */
  explicit mapviewer(QWidget *parent = nullptr);

  /**
   * @brief display_map: creates a scence and a pixmap to display
   * @param map_path: Path to image file or yaml file. Assuming both files are name similarly
   */
  void display_map(const QString map_path);

  /**
   * @brief get_map_resolution: get resolution of map
   * @param map_info_path: Path of yaml file
   */
  void get_map_resolution(const QString map_info_path);

  /**
   * @brief drawDiscretisePath: draws on the map the path created from user input
   */
  void drawDiscretisePath(void);

  QGraphicsScene *scene =  new QGraphicsScene;
  QPixmap *image = new QPixmap;

  QPointF target_viewport_pos, target_scene_pos;
  QList<QPointF> drawnPath;

  Cornu::VectorC<Eigen::Vector2d> _pointsDrawn;
  Cornu::Fitter fitter;
  Cornu::Parameters params;


  float resolution;
  int map_width, map_height, origin_x, origin_y;
  int _panStartX, _panStartY;
  bool _pan;



signals:

public slots:
  /**
   * @brief mouseDoubleClickEvent: Double left click to add points to the map and to the array
   * @param event
   */
  virtual void mouseDoubleClickEvent(QMouseEvent* event);
  /**
   * @brief mousePressEvent: Left click or middle wheel button click to start panning
   * @param event: Click event
   */
  virtual void mousePressEvent(QMouseEvent* event);
  /**
   * @brief mouseReleaseEvent: release left button or middle button to stop panning
   * @param event
   */
  virtual void mouseReleaseEvent(QMouseEvent *event);
  /**
   * @brief mouseMoveEvent: Store mouse position relative to the scene for zooming case
   *                        Set horizontal and vertical scroll bars for panning
   * @param event
   */
  virtual void mouseMoveEvent(QMouseEvent *event);
  /**
   * @brief wheelEvent: rescale the image to zoom and unzoom, set view area to where the mouse is
   * @param event
   */
  virtual void wheelEvent(QWheelEvent *event);


};

#endif // MAPVIEWER_H
