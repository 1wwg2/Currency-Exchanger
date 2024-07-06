#include "mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    WidgetMain = new ExchangerWidget();
    QScreen *screen = QApplication::primaryScreen();
    QRect rect = screen->geometry();
    int x = (rect.width() - this->frameSize().width()) / 2;
    int y = (rect.height() - this->frameSize().height()) / 2;
    this->move(x, y);
    this->resize(350, 400);

    setCentralWidget(WidgetMain);
}

