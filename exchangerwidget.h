#ifndef EXCHANGERWIDGET_H
#define EXCHANGERWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
class ExchangerWidget : public QWidget
{
    Q_OBJECT

public:
    ExchangerWidget(QWidget* parent = nullptr);
protected slots:

private:
    QLabel* InscriptionFrom;
    QLabel* InscriptionTo;
    QLabel* IncorrertTypeEnter;
    QPushButton* Convert;
    QComboBox* ChoiceFirstСurrencyType;
    QComboBox* ChoiceSecondСurrencyType;
    QLineEdit* FirstFormBalance;
    QLineEdit* SecondFormBalance;
};

#endif // EXCHANGERWIDGET_H
