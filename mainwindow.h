#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <QFile>


#include "exchangerwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:
    void DesignAllApp();
    ExchangerWidget* WidgetMain;
};

#endif // MAINWINDOW_H
