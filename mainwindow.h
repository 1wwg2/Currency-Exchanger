#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>

#include "exchangerwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:
    ExchangerWidget* WidgetMain;
};

#endif // MAINWINDOW_H
