#include <myclass.h>


myClass::myClass(){
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));

}
void myClass::fetch(){
    manager->get(QNetworkRequest(QUrl("http://rss.nytimes.com/services/xml/rss/nyt/HomePage.xml")));
}
void myClass::replyFinished(QNetworkReply* pReply){
    QByteArray data = pReply->readAll();
    QString str(data);
    QDebug << str << endl;
}
