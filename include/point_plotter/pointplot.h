#ifndef POINTPLOT_H
#define POINTPLOT_H

#include <QWidget>
#include "ui_pointplot.h"
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
  //void on_fileDirText_textChanged();

private:
    Ui::PointPlot *ui;
};

#endif // POINTPLOT_H
