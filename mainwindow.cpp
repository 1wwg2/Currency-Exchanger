#include "mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
   WidgetMain = new ExchangerWidget();

   this->setFixedSize(350, 400);

    setCentralWidget(WidgetMain);
}

