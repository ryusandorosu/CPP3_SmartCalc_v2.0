#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setFixedSize(600, 651);
  ui->setupUi(this);
  // enabling the enter button on a keyboard
  connect(ui->InputExpressionLine, &QLineEdit::returnPressed, this,
          &MainWindow::on_pushButton_enter_clicked);
  connect(ui->InputExpressionLine, &QLineEdit::returnPressed, this,
          &MainWindow::on_pushButton_plot_clicked);
  connect(ui->InputVarLine, &QLineEdit::returnPressed, this,
          &MainWindow::on_pushButton_enter_clicked);
  connect(ui->InputAxisRangeXmin, &QLineEdit::returnPressed, this,
          &MainWindow::on_pushButton_plot_clicked);
  connect(ui->InputAxisRangeXmax, &QLineEdit::returnPressed, this,
          &MainWindow::on_pushButton_plot_clicked);
  connect(ui->InputAxisRangeYmin, &QLineEdit::returnPressed, this,
          &MainWindow::on_pushButton_plot_clicked);
  connect(ui->InputAxisRangeYmax, &QLineEdit::returnPressed, this,
          &MainWindow::on_pushButton_plot_clicked);
  // allowing only to enter numbers for x variable
  QDoubleValidator *doubleValidator = new QDoubleValidator(this);
  ui->InputVarLine->setValidator(doubleValidator);
  ui->InputAxisRangeXmin->setValidator(doubleValidator);
  ui->InputAxisRangeXmax->setValidator(doubleValidator);
  ui->InputAxisRangeYmin->setValidator(doubleValidator);
  ui->InputAxisRangeYmax->setValidator(doubleValidator);
}

MainWindow::~MainWindow() { delete ui; }

// clean everything (AC)
void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() ==
      Qt::Key_Delete) {  // on mac: cmd + del, ctrl + del, shift + del
    ui->OutputLine->setText("0");
    ui->InputExpressionLine->setText("");
    ui->InputVarLine->setText("");
    ui->InputAxisRangeXmin->setText("-10");
    ui->InputAxisRangeXmax->setText("10");
    ui->InputAxisRangeYmin->setText("-10");
    ui->InputAxisRangeYmax->setText("10");
  }
}

void MainWindow::on_pushButton_enter_clicked() {
  QString expression = ui->InputExpressionLine->text();

  // validation, pt. 2
  if (expression.isEmpty()) {
    ui->OutputLine->setText("expression is empty");
    return;
  }
  if (expression.size() > 255) {
    ui->OutputLine->setText("expression is too large");
    return;
  }
  if (expression.contains("x") && ui->InputVarLine->text().isEmpty()) {
    ui->OutputLine->setText("x value is empty");
    return;
  }

  QRegularExpression allowedSymbols("^[0-9acdgilmnoqrstx()+\\-*\\/^%\\.]+$");
  if (!allowedSymbols.match(expression).hasMatch()) {
    ui->OutputLine->setText("not allowed symbols were entered");
    return;
  }

  QString expressionWithX = expression;
  QString xValue = ui->InputVarLine->text();
  if (expression.contains("x")) {
    expressionWithX.replace("x", xValue);
    if (expressionWithX.size() > 255) {
      ui->OutputLine->setText("expression is too large after x substitution");
      return;
    }
  }

  QByteArray bax = expression.toLocal8Bit();
  char *xval = bax.data();
  if (controller.validateExpression(xval) == 0 && xValue.contains("-")) {
    if (expression.contains("-x")) {
      expression.replace("-x", "-(x)");
    }
    if (expression.contains("+x")) {
      expression.replace("+x", "+(x)");
    }
    if (expression.contains("*x")) {
      expression.replace("*x", "*(x)");
    }
    if (expression.contains("^x")) {
      expression.replace("^x", "^(x)");
    }
    if (expression.contains("/x")) {
      expression.replace("/x", "/(x)");
    }
    if (expression.contains("%x")) {
      expression.replace("%x", "%(x)");
    }
    expression.replace("x", xValue);
  } else if (controller.validateExpression(xval) == 0) {
    expression.replace("x", xValue);
  } else if (controller.validateExpression(xval) == 1 && !xValue.isEmpty()) {
    ui->OutputLine->setText("invalid expression with x");
    return;
  }

  QByteArray bae = expression.toLocal8Bit();
  char *src = bae.data();
  if (controller.validateExpression(src) == 1) {
    ui->OutputLine->setText("invalid expression");
    return;
  }
  // end of validation
  double result = controller.calculateExpression(src);

  QString output = QString::number(result);
  ui->OutputLine->setText(output);
}

void MainWindow::on_pushButton_plot_clicked() {
  QVector<double> x, y;

  ui->widget->clearGraphs();
  x.clear();
  y.clear();
  QString expression = ui->InputExpressionLine->text();
  QString xValue, source;

  QRegularExpression allowedSymbols("^[0-9acdgilmnoqrstx()+\\-*\\/^%\\.]+$");
  if (!allowedSymbols.match(expression).hasMatch()) {
    ui->widget->replot();
    return;
  }
  QByteArray bav = expression.toLocal8Bit();
  char *expr = bav.data();
  if (controller.validateExpression(expr) == 1) {
    ui->widget->replot();
    return;
  }
  if ((ui->InputAxisRangeXmin->text().isEmpty() &&
       ui->InputAxisRangeXmax->text().isEmpty()) &&
      (ui->InputAxisRangeYmin->text().isEmpty() &&
       ui->InputAxisRangeYmax->text().isEmpty())) {
    ui->OutputLine->setText("variable ranges are empty");
    return;
  } else if ((ui->InputAxisRangeXmin->text().isEmpty() ||
              ui->InputAxisRangeXmax->text().isEmpty()) &&
             (ui->InputAxisRangeYmin->text().isEmpty() ||
              ui->InputAxisRangeYmax->text().isEmpty())) {
    ui->OutputLine->setText("variable ranges are not full");
    return;
  }
  if (ui->InputAxisRangeXmin->text().isEmpty() &&
      ui->InputAxisRangeXmax->text().isEmpty()) {
    ui->OutputLine->setText("x variable range is empty");
    return;
  } else if (ui->InputAxisRangeXmin->text().isEmpty()) {
    ui->OutputLine->setText("min x value is empty");
    return;
  } else if (ui->InputAxisRangeXmax->text().isEmpty()) {
    ui->OutputLine->setText("max x value is empty");
    return;
  }
  if (ui->InputAxisRangeYmin->text().isEmpty() &&
      ui->InputAxisRangeYmax->text().isEmpty()) {
    ui->OutputLine->setText("y variable range is empty");
    return;
  } else if (ui->InputAxisRangeYmin->text().isEmpty()) {
    ui->OutputLine->setText("min y value is empty");
    return;
  } else if (ui->InputAxisRangeYmax->text().isEmpty()) {
    ui->OutputLine->setText("max y value is empty");
    return;
  }

  double xBegin = ui->InputAxisRangeXmin->text().toDouble();
  double xEnd = ui->InputAxisRangeXmax->text().toDouble();
  double yBegin = ui->InputAxisRangeYmin->text().toDouble();
  double yEnd = ui->InputAxisRangeYmax->text().toDouble();

  double step = 0.005 * (qFabs(xBegin) + qFabs(xEnd));
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);

  if ((xBegin < -PLOTRANGE || xEnd > PLOTRANGE) &&
      (yBegin < -PLOTRANGE || yEnd > PLOTRANGE)) {
    ui->OutputLine->setText("variables are out of range (-1000000; 1000000)");
    return;
  } else if (xBegin < -PLOTRANGE || xEnd > PLOTRANGE) {
    ui->OutputLine->setText("x variable is out of range (-1000000; 1000000)");
    return;
  } else if (yBegin < -PLOTRANGE || yEnd > PLOTRANGE) {
    ui->OutputLine->setText("y variable is out of range (-1000000; 1000000)");
    return;
  }
  if (!(yBegin < yEnd)) {
    ui->OutputLine->setText(
        "y variable range must be set from lower to higher value");
    return;
  }
  if (xBegin < xEnd) {
    for (double xCalc = xBegin; xCalc <= xEnd; xCalc += step) {
      if (fabs(xCalc) < EPS) {
        xCalc = 0;
      }
      x.push_back(xCalc);
      source = expression;
      xValue = source.replace("x", ('(' + QString::number(xCalc) + ')'));
      QByteArray bag = xValue.toLocal8Bit();
      char *src = bag.data();
      double yCalc = controller.calculateExpression(src);
      y.push_back(yCalc);
    }
  } else {
    ui->OutputLine->setText(
        "x variable range must be set from lower to higher value");
    return;
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}
