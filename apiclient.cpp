#include "apiclient.h"

ApiClient::ApiClient(QObject* parent) : QObject()
{
    manager = new QNetworkAccessManager(this);
}
//"https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange"
void ApiClient::GetAPIInfo(const QString& Site)
{
    QNetworkRequest request((QUrl("https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange")));

    currentReply= manager->get(request);

    connect(currentReply, SIGNAL(finished()), this, SLOT(NetworkReply()));

}

/*Object::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();


            qDebug() << "Decoded String:" << decodedString;
            qDebug() << "Response:" << response;
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();

    });*/
void ApiClient::NetworkReply()
{
    if(currentReply->error() == QNetworkReply::NoError)
    {
        QString decodedString;
        QByteArray response = currentReply->readAll();
        decodedString = QString::fromUtf8(response);
        RemoveTags(decodedString);
        //qDebug() << decodedString;
    }
    else {
        qDebug() << "Error:" << currentReply->errorString(); // Окно ошибки, как и везде
    }
    currentReply->deleteLater();
}

void ApiClient::RemoveTags(const QString &xmlContent)
{
    QXmlStreamReader xml(xmlContent);
    DataFromXML.reserve(300);
    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();
        if (xml.isCharacters() && !xml.isWhitespace())
        {
            DataFromXML.push_back(xml.text().toString());
        }
    }
    FillInMap();
    if (xml.hasError())
    {
        qDebug() << "Error parsing XML:" << xml.errorString();
    }
}

void ApiClient::FillInMap()
{
    for(int i = 0; i < DataFromXML.size(); ++i)
    {
        bool isCorrect = true;
        for(const QChar& ch : DataFromXML[i])
        {
            if(!ch.isLetter() || !ch.isUpper())
            {
                isCorrect = false;
                break;
            }
        }
        if(isCorrect)
        {
            qDebug() << DataFromXML[i];
            qDebug() << DataFromXML[i - 1];
        }
    }
}
