#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rss.h"
#include "newsmap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <QDesktopServices> //for opening a url in browser

/*
 *mainwindow.cpp controls the events that happen in the GUI's window widget,
 * therefore, most actions and method calls will be here.
*/
using namespace std;
//Creates MainWindow object and the ui namespace.
//This ui namespace is a container for every widget in the MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Welcome to the New York Times News Feed!");
    ui->listWidget->addItem("Please select a source from the right, then click GO");
}

MainWindow::~MainWindow()
{
    delete ui;
}

NewsMap *rssNews; //rssNews object must be in this scope to allow other widgets to use it
void MainWindow::on_goButton_clicked()
{
    ui->listWidget->clear(); //clears listWidget of any text
    QString selection = ui->comboBox->currentText(); //get combobox selection
    ui->listWidget->addItem(selection); //add to listWidget
    ui->listWidget->addItem("--------------------------------------------");
    QString addr;
    if(selection == "Home Page - New York Times"){ //finds appropriate URL from selection
        addr = "http://rss.nytimes.com/services/xml/rss/nyt/HomePage.xml";
    }else if(selection == "World News - New York Times"){
        addr = "http://rss.nytimes.com/services/xml/rss/nyt/World.xml";
    }else if(selection == "US News - New York Times"){
        addr = "http://rss.nytimes.com/services/xml/rss/nyt/US.xml";
    }else if(selection == "Tech News - New York Times"){
        addr = "http://rss.nytimes.com/services/xml/rss/nyt/Technology.xml";
    }else if(selection == "Art News - New York Times"){
        addr = "http://rss.nytimes.com/services/xml/rss/nyt/Arts.xml";
    }
    //Creates new RSS object which will connect to the website, read the data to a .txt file
    RSS *feed = new RSS(addr);
    rssNews = new NewsMap();
    rssNews->populateMap(); //reads from file into map
    //iterate through map and post news articles to listWidget
    for(map<QString, QString>::const_iterator it = rssNews->news->begin(); it != rssNews->news->end(); ++it){
        QString item = it->first; //get title and description
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_clearButton_clicked()
{
    ui->listWidget->clear(); //clears listWidget
}

void MainWindow::on_searchButton_clicked()
{
    if(ui->lineEdit->text() == ""){ //if nothing typed, do nothing
        return;
    }
    string searchInput = ui->lineEdit->text().toStdString();
    //create a vector of results
    vector<QString> findings = rssNews->searchMap(searchInput);
    ui->listWidget->clear();
    //print the results
    for(int i = 0; i<findings.size(); i++){
        ui->listWidget->addItem(findings.at(i));
    }
}

void MainWindow::on_browserButton_clicked()
{
    if(ui->listWidget->currentItem() == NULL){ //if nothing selected, do nothing
        return;
    }
    QString link;
    QString selected = ui->listWidget->currentItem()->text(); //get text of item selected
    //match text to one in map and get link
    for(map<QString, QString>::const_iterator it = rssNews->news->begin(); it != rssNews->news->end(); ++it){
        QString item = it->first;
        if(item == selected){
            link = it->second;
        }
    }
    string stdLink = link.toStdString();
    if(link == "\0" || stdLink.find("http:") == string::npos){ //if there is no link, do nothing
        return;
    }
    QUrl url(link); //Creates QUrl encoded url
    QDesktopServices::openUrl(url); //sends url to default browser on computer
}
