#ifndef POINTPLOT_H
#define POINTPLOT_H

#include "ui_pointplot.h"
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QLayout>
#include <QSplitter>
#include <QFileDialog>

namespace Ui {
class PointPlot;
}

class PointPlot : public QWidget
{
    Q_OBJECT

public:
    explicit PointPlot(QWidget *parent = 0);
    ~PointPlot();
    QString map_path, map_info_path;

private slots:
  void on_fileDir_clicked();
  void on_plotPointButton_clicked();
  void on_clearPointButton_clicked();
  void on_runButton_clicked();
  void on_stopButton_clicked();
  void on_quitButton_clicked();


private:
    Ui::PointPlot *ui;
};

#endif // POINTPLOT_H
