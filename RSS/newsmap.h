#ifndef NEWSMAP_H
#define NEWSMAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <QString>
using namespace std;
//Creates an object with a map in order to facilitate efficiency and organization
class NewsMap{
public:
    map<QString, QString> * news;
    NewsMap();
    void populateMap();
    vector<QString> searchMap(string);
};

#endif // NEWSMAP_H
