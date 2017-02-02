#include "rss.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <iostream>
#include <QDebug>
#include <cstdlib>


using namespace std;
//Create RSS Object
RSS::RSS(QString addr){
    QUrl url(addr);
    manager = new QNetworkAccessManager(this); //create NetworkAccessManager
    //connect the manager to the reply slot to know when it successfully connects and finishes connection
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    RSSRead(url); //Read data from URL selected
}
void RSS::fetch(QUrl url){ //send request and get answer from connection to site
    manager->get(QNetworkRequest(url)); //automatically calls replyFinished() when reply is received
}
void RSS::replyFinished(QNetworkReply * reply){ //get signal when connection is finished
    QByteArray data = reply->readAll(); //read all data received from connection (all xml data)
    QString str(data); //convert QByteArray to QString
    createDataFile(str); //create a file with the data to save it
}
//At this point, the Console may print warnings regarding to not being able
//to resolve SSL functions. These can be ignored.
void RSS::RSSRead(QUrl addr){
    fetch(addr);
}
//createDataFile() creates a text file to save the data to so it is useable by the GUI.
//If the data is not saved in this way, it will get deleted immediately. A file must be created outside
//of this object and network connection in order for any data to be saved. Attempting to send the data
//to another object or parameter will fail. (I tried it many ways, this one worked and let me incorporate
//file reading/writing into this project)
void RSS::createDataFile(QString data){
    ofstream outDataFile("data.txt", ios::out);
    if(!outDataFile){ //check if file is available
        cout << "Data could not be saved" << endl;
        exit(1);
    }
    outDataFile << data.toStdString(); //convert from QString to std string and print to file
}
