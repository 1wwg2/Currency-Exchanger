#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QString>
#include <QMessageBox>

#include "customvalidator.h"
#include "exchangerwidget.h"


ExchangerWidget::ExchangerWidget(QWidget* parent) : QWidget(parent)
{
    InitializationComponents();
    SetObjectOnWindow();

    connect(Convert, SIGNAL(clicked()), this, SLOT(MakeConvert()));
    connect(ChoiceFirstСurrencyType, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChangedFirst(int)));
    connect(ChoiceSecondСurrencyType, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChangedSecond(int)));
}

void ExchangerWidget::MakeConvert()
{

    if(FirstFormBalance->text().isEmpty())
    {
        SecondFormBalance->setText("");
        QMessageBox::information(this, "Warning!",
                                 "Nothing to convert",
                                 QMessageBox::Close,
                                 QMessageBox::Close);
    }
    else
    {
        QString From = ChoiceFirstСurrencyType->currentText();
        QString To = ChoiceSecondСurrencyType->currentText();
        double Amount = FirstFormBalance->text().toDouble();

        double FromRate = ExchangeRates[From];
        double ToRate = ExchangeRates[To];
        double Result = (Amount / FromRate) * ToRate;


        QString answerOnRequest = QString::number(Result, 'f', 2);

        SecondFormBalance->setText(answerOnRequest);
    }

}

void ExchangerWidget::InitializationComponents()
{
    InscriptionFrom = new QLabel("From:",this);
    InscriptionTo = new QLabel("To:",this);
    IncorrertTypeEnter = new QLabel("Incorrect type");
    Convert = new QPushButton("Convert money");

    FirstFormBalance = new QLineEdit(this);
    FirstFormBalance->setPlaceholderText("Enter value to convert:");
    SecondFormBalance = new QLineEdit(this);
    SecondFormBalance->setReadOnly(true);
    SecondFormBalance->setFocusPolicy(Qt::NoFocus);
    ChoiceFirstСurrencyType = new QComboBox(this);
    ChoiceSecondСurrencyType = new QComboBox(this);

    Convert = new QPushButton("Convert type");

    FirstFormBalance->setValidator(new CustomValidator(this));
    SecondFormBalance->setValidator(new CustomValidator(this));

    InitializationComboBox();

    PreviousIndexFirstBox = ChoiceFirstСurrencyType->currentIndex();
    PreviousIndexSecondBox = ChoiceSecondСurrencyType->currentIndex();

}

void ExchangerWidget::InitializationComboBox()
{
    //Идея: Вектор с названиями, берем строку, добавляем в путь, строка и картинка в той же кодировке (UAH.png and UAH)
    //Возможно при переносе на другой ПК отвалятся иконки!!!
    /*TODO: сделать енам, подумать про масштабирование картинок + вектора, скорее всего использовать мапу*/
    enum class СurrenciesName
    {
        USD,
        UAH,
        EURO,
        RUB
    };

    QVector<QString> VectorOfСurrencies = {"USD","UAH", "EUR", "RUB", "RMB"};

    for(int i = 0; i < VectorOfСurrencies.size(); ++i)
    {
        QString NameOfCurrency = VectorOfСurrencies.at(i);
        ChoiceFirstСurrencyType->addItem(QIcon(":/resources/images/" + NameOfCurrency), NameOfCurrency);
        ChoiceSecondСurrencyType->addItem(QIcon(":/resources/images/" + NameOfCurrency), NameOfCurrency);
    }
    ChoiceFirstСurrencyType->setCurrentIndex(0);
    ChoiceSecondСurrencyType->setCurrentIndex(1);


    ExchangeRates[VectorOfСurrencies[0]] = 1.0;
    ExchangeRates[VectorOfСurrencies[1]] = 41.03;
    ExchangeRates[VectorOfСurrencies[2]] = 0.92;
}

void ExchangerWidget::SetObjectOnWindow()
{
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

}

void ExchangerWidget::onComboBoxIndexChangedFirst(int index)
{

    int CurrIndexSecondBox = ChoiceSecondСurrencyType->currentIndex();
    if (index == CurrIndexSecondBox)
    {
        ChoiceSecondСurrencyType->setCurrentIndex(PreviousIndexFirstBox);
    }
    else
    {
        PreviousIndexFirstBox = index;
    }

}

void ExchangerWidget::onComboBoxIndexChangedSecond(int index)
{
    int CurrIndexFirstBox = ChoiceFirstСurrencyType->currentIndex();
    if (index == CurrIndexFirstBox)
    {
        ChoiceFirstСurrencyType->setCurrentIndex(PreviousIndexSecondBox);
    }
    else
    {
        PreviousIndexSecondBox = index;
    }

}








