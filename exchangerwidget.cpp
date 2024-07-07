#include "exchangerwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QString>

ExchangerWidget::ExchangerWidget(QWidget* parent) : QWidget(parent)
{
    InscriptionFrom = new QLabel("From:",this);
    InscriptionTo = new QLabel("To:",this);
    IncorrertTypeEnter = new QLabel("Incorrect type");
    Convert = new QPushButton("Convert money");

    FirstFormBalance = new QLineEdit(this);
    SecondFormBalance = new QLineEdit(this);
    SecondFormBalance->setReadOnly(true);
    SecondFormBalance->setFocusPolicy(Qt::NoFocus);
    ChoiceFirstСurrencyType = new QComboBox(this);
    ChoiceSecondСurrencyType = new QComboBox(this);

    Convert = new QPushButton("Convert type");

    FirstFormBalance->setValidator(new QDoubleValidator(this));
    SecondFormBalance->setValidator(new QDoubleValidator(this));

    ChoiceFirstСurrencyType->addItem("Item 1");
    ChoiceFirstСurrencyType->addItem("Item 2");
    ChoiceFirstСurrencyType->addItem("Item 3");

    ChoiceSecondСurrencyType->addItem("Item 1");
    ChoiceSecondСurrencyType->addItem("Item 2");
    ChoiceSecondСurrencyType->addItem("Item 3");

    QVBoxLayout* LabelNChoise = new QVBoxLayout();
    LabelNChoise->addWidget(InscriptionFrom);

    QHBoxLayout* LineEdit = new QHBoxLayout();
    LineEdit->setContentsMargins(0, 0, 0, 0);
    LineEdit->setSpacing(0);
    LineEdit->addWidget(ChoiceFirstСurrencyType);
    LineEdit->addWidget(FirstFormBalance);

    QVBoxLayout* LabelNChoiseSecond = new QVBoxLayout();
    LabelNChoiseSecond->addWidget(InscriptionTo);

    QHBoxLayout* LineEditSecond = new QHBoxLayout();
    LineEditSecond->setContentsMargins(0, 0, 0, 0);
    LineEditSecond->setSpacing(0);
    LineEditSecond->addWidget(ChoiceSecondСurrencyType);
    LineEditSecond->addWidget(SecondFormBalance);

    LabelNChoise->addLayout(LineEdit);
    LabelNChoiseSecond->addLayout(LineEditSecond);

    QVBoxLayout* mainContainer = new QVBoxLayout();
    mainContainer->addLayout(LabelNChoise);
    mainContainer->setSpacing(5);
    mainContainer->addLayout(LabelNChoiseSecond);
    mainContainer->addWidget(Convert);

    setLayout(mainContainer);

    connect(Convert, SIGNAL(clicked()), this, SLOT(MakeConvert()));

}

void ExchangerWidget::MakeConvert()
{
    const double dollar = 0.025;
    double value = 0.0;
    QString buffer = FirstFormBalance->text();
    (value = buffer.toDouble()) *= dollar;
    QString answerOnRequest = QString::number(value, 'f', 2);

    SecondFormBalance->setText(answerOnRequest);
}

