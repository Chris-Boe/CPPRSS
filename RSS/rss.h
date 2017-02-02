#ifndef RSS_H
#define RSS_H

#include <map>
#include <list>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <iostream>
#include <QDebug>
#include <QUrl>
#include <fstream>

using namespace std;
//This RSS object creates a path to a URL, sends a request, then receives a reply if the
//connection is good. The QObject inheritance allows for slots, and the proper use of other
//Qt Library objects
class RSS : public QObject{
    Q_OBJECT
private:
    QNetworkAccessManager* manager;
public:
    RSS(QString);
    void RSSRead(QUrl);
    void createDataFile(QString);
    //network functions
    void fetch(QUrl);
public slots:
    void replyFinished(QNetworkReply*);
};


#endif // RSS_H
