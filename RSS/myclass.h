#ifndef MYCLASS_H
#define MYCLASS_H
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <iostream>
#include <QDebug>
#include <QUrl>
class myClass : public QObject{
    Q_OBJECT
public:
    myClass();
    void fetch();

public slots:
    void replyFinished(QNetworkReply*);

private:
    QNetworkAccessManager* manager;
};

#endif // MYCLASS_H
