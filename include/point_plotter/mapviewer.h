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

#define prius_width  1.76
#define prius_length 4.5

class mapviewer : public QGraphicsView
{
  Q_OBJECT
public:
  explicit mapviewer(QWidget *parent = nullptr);
  void display_map(const QString map_path);
  void get_map_resolution(const QString map_info_path);

  QGraphicsScene *scene =  new QGraphicsScene;
  QPixmap *image = new QPixmap;
  int map_width, map_height, origin_x, origin_y;
  float resolution;
  bool _pan;
  int _panStartX, _panStartY;
  QPointF target_viewport_pos, target_scene_pos;

signals:

public slots:
  virtual void mouseDoubleClickEvent(QMouseEvent* event);
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual void wheelEvent(QWheelEvent *event);


};

#endif // MAPVIEWER_H
