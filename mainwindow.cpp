#include "mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
   WidgetMain = new ExchangerWidget();
   /*QList<QScreen*> screens = QApplication::screens();
   QScreen* secondScreen = QApplication::primaryScreen();
   QRect rect = secondScreen->geometry();
   int x = (rect.width() - this->frameSize().width()) / 2;
   int y = (rect.height() - this->frameSize().height()) / 2;
   this->move(x, y);*/
   this->setFixedSize(350, 400);

    setCentralWidget(WidgetMain);
}

