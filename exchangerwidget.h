#ifndef EXCHANGERWIDGET_H
#define EXCHANGERWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QMap>

#include "apiclient.h"
class ExchangerWidget : public QWidget
{
    Q_OBJECT

public:
    ExchangerWidget(QWidget* parent = nullptr);
protected slots:
    void MakeConvert();
    void onComboBoxIndexChangedFirst(int);
    void onComboBoxIndexChangedSecond(int);

private:
    void InitializationComponents();
    void SetObjectOnWindow();
    void InitializationComboBox();
    void ConnectToActualCurrencies();
    QLabel* InscriptionFrom;
    QLabel* InscriptionTo;
    QLabel* IncorrertTypeEnter;
    QPushButton* Convert;
    QComboBox* ChoiceFirstСurrencyType;
    QComboBox* ChoiceSecondСurrencyType;
    QLineEdit* FirstFormBalance;
    QLineEdit* SecondFormBalance;
    QMap<QString, double> ExchangeRates;
    ApiClient* DataForMapCurrency;
    QVector<QString> VectorOfСurrencies;

    int PreviousIndexFirstBox;
    int PreviousIndexSecondBox;
};

#endif // EXCHANGERWIDGET_H
