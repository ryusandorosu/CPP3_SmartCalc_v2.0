#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDoubleValidator>
#include <QKeyEvent>
#include <QMainWindow>
#include <QRegularExpressionValidator>

#include "resources/qcustomplot.h"

#define EPS 1e-7
#define PLOTRANGE 1000000

//#include "../model/backend.h"
#include "../model/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::Controller controller;

 private slots:
  void on_pushButton_enter_clicked();
  void on_pushButton_plot_clicked();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
};

#endif  // MAINWINDOW_H
