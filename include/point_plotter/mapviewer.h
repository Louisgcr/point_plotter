#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

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

signals:

public slots:
  void mousePressEvent(QMouseEvent* event);
};

#endif // MAPVIEWER_H
