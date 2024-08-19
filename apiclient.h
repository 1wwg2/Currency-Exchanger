#ifndef APICLIENT_H
#define APICLIENT_H


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QXmlStreamReader>
#include <QMap>

class ApiClient : public QObject
{
     Q_OBJECT
public:
   explicit ApiClient(QObject* parent = nullptr);
    void GetAPIInfo(const QString& SiteName);
    void FillInMap();
    QMap<QString, double> GetMapWithFilterData() const;
private slots:
    void NetworkReply();
private:
    void RemoveTags(const QString &xmlContent);


    QNetworkAccessManager* manager;
    QNetworkReply* currentReply;
    QVector<QString> DataFromXML;
    QMap<QString, double> MapWithFilterData;

};

#endif // APICLIENT_H
