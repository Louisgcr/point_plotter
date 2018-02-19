#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

class mapviewer : public QGraphicsView
{
  Q_OBJECT
public:
  explicit mapviewer(QWidget *parent = nullptr);
  void display_map(const QString map_path);

signals:

public slots:
  void mousePressEvent(QMouseEvent* event);
};

#endif // MAPVIEWER_H
