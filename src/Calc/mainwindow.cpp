#include "mainwindow.h"

#include <QDebug>
#include <QDoubleValidator>

#include "../s21_controller.h"
#include "./ui_mainwindow.h"
#include "qcustomplot.h"

QString expression;
QString currentX;

MainWindow::MainWindow(s21::Controller *control, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), control(control) {
  ui->setupUi(this);
  ui->result_show->setText("");

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(ButtonActive()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(ButtonActive()));

  //   connect(ui->pushButton_point, SIGNAL(clicked()), this,
  //           SLOT(on_pushButton_point_clicked()));

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(ButtonActiveNotX()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this,
          SLOT(ButtonActiveNotX()));
  connect(ui->pushButton_multiplication, SIGNAL(clicked()), this,
          SLOT(ButtonActiveNotX()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(ButtonActiveNotX()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(ButtonActiveNotX()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(ButtonActiveNotX()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this,
          SLOT(ButtonActiveNotX()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this,
          SLOT(ButtonActiveNotX()));

  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(ButtonFunctionsActive()));

  auto val = new QDoubleValidator;

  QLocale lo(QLocale::C);
  lo.setNumberOptions(QLocale::RejectGroupSeparator);
  val->setLocale(lo);
  ui->lineEdit_x->setValidator(val);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ButtonActive() {
  if (ui->lineEdit_expression->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    expression = ui->lineEdit_expression->text() + button->text();
    ui->lineEdit_expression->setText(expression);
  } else if (ui->lineEdit_x->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    currentX = ui->lineEdit_x->text() + button->text();
    ui->lineEdit_x->setText(currentX);
  }
}

void MainWindow::ButtonActiveNotX() {
  if (ui->lineEdit_expression->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    expression = ui->lineEdit_expression->text() + button->text();
    ui->lineEdit_expression->setText(expression);
  }
}

void MainWindow::ButtonFunctionsActive() {
  if (ui->lineEdit_expression->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    expression = ui->lineEdit_expression->text() + button->text() + "(";
    ui->lineEdit_expression->setText(expression);
  }
}

void MainWindow::on_pushButton_pow_clicked() {
  if (ui->lineEdit_expression->hasFocus()) {
    expression = ui->lineEdit_expression->text() + "^";
    ui->lineEdit_expression->setText(expression);
  }
}

void MainWindow::on_pushButton_AC_clicked() {
  ui->result_show->setText("");
  ui->show_error->setText("");
  ui->lineEdit_expression->setText("");
  ui->lineEdit_x->setText("");
}

void MainWindow::on_pushButton_CE_clicked() {
  if (ui->lineEdit_expression->hasFocus()) {
    QString currentText = ui->lineEdit_expression->text();
    if (!currentText.isEmpty()) {
      currentText.chop(1);
      ui->lineEdit_expression->setText(currentText);
      expression = ui->lineEdit_expression->text();
    }
  }
  if (ui->lineEdit_x->hasFocus()) {
    currentX = ui->lineEdit_x->text();
    if (!currentX.isEmpty()) {
      currentX.chop(1);
      ui->lineEdit_x->setText(currentX);
    }
  }
}

void MainWindow::on_pushButton_point_clicked() {
  if (ui->lineEdit_expression->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    expression = ui->lineEdit_expression->text() + button->text();
    ui->lineEdit_expression->setText(ui->lineEdit_expression->text() +
                                     button->text());
  } else if (ui->lineEdit_x->hasFocus() && !ui->lineEdit_x->text().isEmpty()) {
    if (!(ui->lineEdit_x->text().contains('.'))) {
      ui->lineEdit_x->setText(ui->lineEdit_x->text() + ".");
    }
  }
}

void MainWindow::on_pushButton_equals_clicked() {
  if (!ui->result_show->text().isEmpty()) ui->result_show->setText("");
  if (!ui->show_error->text().isEmpty()) ui->show_error->setText("");
  if (ui->lineEdit_x->text().isEmpty()) ui->lineEdit_x->setText("0");
  QString input_QS = ui->lineEdit_expression->text();
  std::string input_expression = input_QS.toStdString();
  double result = 0.0;
  QString currentX = ui->lineEdit_x->text();
  double x_val = currentX.toDouble();
  try {
    result = control->Calculate(input_expression, x_val);
    QString output = QString::number(result);
    ui->result_show->setText(output);
  } catch (const std::exception &e) {
    QString error_message = QString::fromStdString(e.what());
    ui->show_error->setText(error_message);
  }
  // qDebug() << error;
  // if (error > 0) {
  //   ui->show_error->setText("Invalid input");
  // }
}

void MainWindow::on_pushButton_plot_graph_clicked() {
  ui->graph->clearGraphs();
  ui->result_show->setText("");
  ui->show_error->setText("");
  try {
      GraphParams params;
      params.xMin = ui->doubleSpinBox_x_min->value();
      params.xMax = ui->doubleSpinBox_x_max->value();
      params.yMin = ui->doubleSpinBox_y_min->value();
      params.yMax = ui->doubleSpinBox_y_max->value();
      params.formula = ui->lineEdit_expression->text().toStdString();
//      QScreen *screen = QGuiApplication::primaryScreen();
//      QRect screenGeometry = screen->geometry();
//      int width = screenGeometry.width();

      params.step = (params.xMax - params.xMin) / 499.;

      ui->graph->xAxis->setRange(params.xMin, params.xMax);
      ui->graph->yAxis->setRange(params.yMin, params.yMax);
      ui->graph->replot();

      if (params.xMin > params.xMax) {
        ui->show_error->setText("error: min x > max x");
      } else if (params.yMin > params.yMax) {
        ui->show_error->setText("error: min y > max y");
      } else if (params.yMin == params.yMax || params.xMin == params.xMax) {
        ui->show_error->setText("error: min and max are the same");
      } else {
        std::vector<std::pair<double, double>> graphData =
            control->CalculateGraph(params);
        QVector<double> arrayX, arrayY;
        for (const auto &point : graphData) {
          arrayX.push_back(point.first);
          arrayY.push_back(point.second);
        }
//        qDebug() << arrayX.size();
        ui->graph->addGraph();
        ui->graph->graph(0)->setData(arrayX, arrayY);
        ui->graph->xAxis->setLabel("x");
        ui->graph->yAxis->setLabel("y");
        ui->graph->xAxis->setRange(params.xMin, params.xMax);
        ui->graph->yAxis->setRange(params.yMin, params.yMax);
        ui->graph->replot();
      }
  } catch (const std::exception &e) {
    QString error_message = QString::fromStdString(e.what());
    ui->show_error->setText(error_message);
  }
}
