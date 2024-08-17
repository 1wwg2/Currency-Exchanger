#ifndef APICLIENT_H
#define APICLIENT_H


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QXmlStreamReader>

class ApiClient : public QObject
{
     Q_OBJECT
public:
   explicit ApiClient(QObject* parent = nullptr);
    void GetAPIInfo(const QString& SiteName);
private slots:
    void NetworkReply();
private:
    void RemoveTags(const QString &xmlContent);
    void FillInMap();

    QNetworkAccessManager* manager;
    QNetworkReply* currentReply;
    QVector<QString> DataFromXML;

};

#endif // APICLIENT_H
