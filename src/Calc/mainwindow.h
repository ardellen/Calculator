#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qvector.h>

#include <QMainWindow>
#include <string>

#include "../s21_controller.h"
#include "../s21_model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
namespace s21 {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *control, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::Controller *control;

 private slots:
  void ButtonActive();
  void ButtonFunctionsActive();
  void on_pushButton_AC_clicked();
  void on_pushButton_CE_clicked();
  void on_pushButton_equals_clicked();
  void on_pushButton_pow_clicked();
  void ButtonActiveNotX();
  void on_pushButton_point_clicked();

  void on_pushButton_plot_graph_clicked();
};
#endif  // MAINWINDOW_H
