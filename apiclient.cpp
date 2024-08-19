#include "apiclient.h"

ApiClient::ApiClient(QObject* parent) : QObject()
{
    manager = new QNetworkAccessManager(this);
}
//"https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange"
void ApiClient::GetAPIInfo(const QString& Site)
{
    QNetworkRequest request((QUrl(Site)));

    currentReply= manager->get(request);

    connect(currentReply, SIGNAL(finished()), this, SLOT(NetworkReply()));

}

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
    if (xml.hasError())
    {
        qDebug() << "Error parsing XML:" << xml.errorString();
    }
    FillInMap();

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
            MapWithFilterData.insert(DataFromXML[i], DataFromXML[i - 1].toDouble());
        }
    }

    /*for (auto it = MapWithFilterData.begin(); it != MapWithFilterData.end(); ++it)
      {
        qDebug() << "Key:" << it.key() << ", Value:" << it.value();
      }
 */
      // qDebug() << MapWithFilterData.size();

}



QMap<QString, double> ApiClient::GetMapWithFilterData() const
{
    return MapWithFilterData;
}
