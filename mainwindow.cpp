#include "mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
   WidgetMain = new ExchangerWidget();

   this->setFixedSize(350, 400);
   this->setWindowIcon(QIcon(":/resources/images/IconMoney.png"));
    setCentralWidget(WidgetMain);
}

