#include "mainwindow.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
   WidgetMain = new ExchangerWidget();

   this->setFixedSize(350, 400);
   this->setWindowIcon(QIcon(":/resources/images/IconMoney.png"));

   setCentralWidget(WidgetMain);
   DesignAllApp();
}

void MainWindow::DesignAllApp()
{
    QFile file(":/resources/styles/currencystyle.css");
    if (file.open(QIODevice::ReadOnly)) {
        setStyleSheet(file.readAll());
        file.close();
    }
}
