#include "customvalidator.h"
#include "exchangerwidget.h"
#include "apiclient.h"

ExchangerWidget::ExchangerWidget(QWidget* parent) : QWidget(parent)
{
    VectorOfСurrencies = {"UAH", "USD", "EUR", "RUB", "CZK"};

    InitializationComponents();
    SetObjectOnWindow();

    connect(Convert, SIGNAL(clicked()), this, SLOT(MakeConvert()));
    connect(ChoiceFirstСurrencyType, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChangedFirst(int)));
    connect(ChoiceSecondСurrencyType, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChangedSecond(int)));
}

void ExchangerWidget::MakeConvert()
{
    ConnectToActualCurrencies();

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

        double ToRate = ExchangeRates[To];
        double FromRate = ExchangeRates[From];
        double Result = (Amount / ToRate) * FromRate;


        QString answerOnRequest = QString::number(Result, 'f', 2);

        SecondFormBalance->setText(answerOnRequest);
    }

}

void ExchangerWidget::InitializationComponents()
{
    DataForMapCurrency = new ApiClient(this);
    DataForMapCurrency->GetAPIInfo("https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange");

    InscriptionFrom = new QLabel("From:",this);

    InscriptionTo = new QLabel("To:",this);

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

    SetObjectNameForComponents();
}

void ExchangerWidget::InitializationComboBox()
{
    for(int i = 0; i < VectorOfСurrencies.size(); ++i)
    {
        QString NameOfCurrency = VectorOfСurrencies.at(i);
        ChoiceFirstСurrencyType->addItem(QIcon(":/resources/images/" + NameOfCurrency), NameOfCurrency);
        ChoiceSecondСurrencyType->addItem(QIcon(":/resources/images/" + NameOfCurrency), NameOfCurrency);
    }

    ChoiceFirstСurrencyType->setCurrentIndex(0);
    ChoiceFirstСurrencyType->setMinimumWidth(85);
    ChoiceSecondСurrencyType->setCurrentIndex(1);
    ChoiceSecondСurrencyType->setMinimumWidth(85);
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
    mainContainer->setSpacing(0);
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

void ExchangerWidget::ConnectToActualCurrencies()
{
    ExchangeRates = DataForMapCurrency->GetMapWithFilterData();

    QSet<QString> validCurrencies(VectorOfСurrencies.begin(), VectorOfСurrencies.end());
    QMap<QString, double> filteredRates;

    for (auto it = ExchangeRates.constBegin(); it != ExchangeRates.constEnd(); ++it)
    {
        if (validCurrencies.contains(it.key()))
        {
            filteredRates.insert(it.key(), it.value());
        }
    }
    filteredRates.insert("UAH", 1);
    ExchangeRates = filteredRates;
}

void ExchangerWidget::SetObjectNameForComponents()
{
    InscriptionFrom->setObjectName("InscriptionFrom");
    InscriptionTo->setObjectName("InscriptionTo");
    Convert->setObjectName("Convert");
    ChoiceFirstСurrencyType->setObjectName("ChoiceFirstСurrencyType");
    ChoiceSecondСurrencyType->setObjectName("ChoiceSecondСurrencyType");
    FirstFormBalance->setObjectName("FirstFormBalance");
    SecondFormBalance->setObjectName("SecondFormBalance");
}





