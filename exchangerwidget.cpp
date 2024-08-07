#include "exchangerwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleValidator>

ExchangerWidget::ExchangerWidget(QWidget* parent) : QWidget(parent)
{
    InscriptionFrom = new QLabel("From:");
    InscriptionTo = new QLabel("To:");
    Convert = new QPushButton("Convert money");
    FirstFormBalance = new QLineEdit();
    SecondFormBalance = new QLineEdit();
    ChoiceFirstСurrencyType = new QComboBox();
    ChoiceSecondСurrencyType = new QComboBox();
    Convert = new QPushButton("Convert type");

    FirstFormBalance->setValidator(new QDoubleValidator());
    SecondFormBalance->setValidator(new QDoubleValidator());

    ChoiceFirstСurrencyType->addItem("Item 1");
    ChoiceFirstСurrencyType->addItem("Item 2");
    ChoiceFirstСurrencyType->addItem("Item 3");

    ChoiceSecondСurrencyType->addItem("Item 1");
    ChoiceSecondСurrencyType->addItem("Item 2");
    ChoiceSecondСurrencyType->addItem("Item 3");

    QVBoxLayout* LabelNChoise = new QVBoxLayout();
    LabelNChoise->addWidget(InscriptionFrom);

    QHBoxLayout* LineEdit = new QHBoxLayout();
    LineEdit->addWidget(ChoiceFirstСurrencyType);
    LineEdit->addWidget(FirstFormBalance);

    QVBoxLayout* LabelNChoiseSecond = new QVBoxLayout();
    LabelNChoiseSecond->addWidget(InscriptionTo);

    QHBoxLayout* LineEditSecond = new QHBoxLayout();
    LineEditSecond->addWidget(ChoiceSecondСurrencyType);
    LineEditSecond->addWidget(SecondFormBalance);

    LabelNChoise->addLayout(LineEdit);
    LabelNChoiseSecond->addLayout(LineEditSecond);

    QVBoxLayout* mainContainer = new QVBoxLayout();
    mainContainer->addLayout(LabelNChoise);
    mainContainer->addLayout(LabelNChoiseSecond);
    mainContainer->addWidget(Convert);
    setLayout(mainContainer);
}
