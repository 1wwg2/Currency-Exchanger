#include "apiclient.h"

ApiClient::ApiClient(QWidget* parent) : QWidget(parent)
{
    manager = new QNetworkAccessManager(this);

}

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
    }
    else
    {
        qDebug() << "Error:" << currentReply->errorString();
        QMessageBox msgBox(QMessageBox::Warning, "Warning!", "Error connect to API!:", QMessageBox::Close, this);
        if (msgBox.exec() == QMessageBox::Close)
        {
            QApplication::quit();
        }
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
        QMessageBox msgBox(QMessageBox::Warning, "Warning!", "Error parsing XML:", QMessageBox::Close, this);
        if (msgBox.exec() == QMessageBox::Close)
        {
            QApplication::quit();
        }
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
}

QMap<QString, double> ApiClient::GetMapWithFilterData() const
{
    return MapWithFilterData;
}
