#include <newsmap.h>
#include <QUrl>
using namespace std;

NewsMap::NewsMap(){
    news = new map<QString, QString>();
}
//fill object map with data
void NewsMap::populateMap(){

    ifstream inDataFile("data.txt", ios::in);
    if(!inDataFile){
        cout << "File could not be opened" << endl;
        exit(1);
    }
    //skip to first news item in xml
    //XML files have lots of introductory info
    inDataFile.seekg(0); //start at beginning
    while(!inDataFile.eof()){
        string line;
        getline(inDataFile, line);
        if(line.find("<item>") != string::npos){ //stop when we find the first item
            break;
        }else{
            continue;
        }
    }
    QString title;
    QString description;
    QString link;
    while(!inDataFile.eof()){ //read until end of file
        string line;
        getline(inDataFile,line); //read in line
        //if line contains <title> or <description>, etc. Read the line into the appropriate variable
        //then trim off the tags at the beginning and end using the line.substr() method
        if(line.find("<title>") != string::npos){
            line = line.substr(line.find_first_of(">")+1, line.find_last_of("<")-13);
            title = QString::fromStdString(line);
        }else if(line.find("<description>") != string::npos){
            line = line.substr(line.find_first_of(">")+1, line.find_last_of("<")-19);
            description = QString::fromStdString(line);
        }else if(line.find("<link") != string::npos){
            line = line.substr(line.find_first_of(">")+1, line.find_last_of("<")-10);
            link = QString::fromStdString(line);
        }else if(line.find("</item>") != string::npos){//at end of item
            title += "\n--" + description; // title and description
            news->insert(make_pair(title, link)); //make pair and insert into map
            title = ""; //reset variables for next <item>
            description = "";
            link = "";
        }
    }
}
//Iterate through map and return any results that contain the searchInput
//this could be in the title or description of the object, located in the map's
//first attribute
//returns a vector of the results
vector<QString> NewsMap::searchMap(string searchInput){
    //instantiate variables
    vector<QString> results;
    string item;
    QString qItem;
    string category;
    //iterate through map and find any references to searchInput
    for(map<QString, QString>::const_iterator it1 = news->begin(); it1 != news->end(); ++it1){
        item = it1->first.toStdString(); //convert to std string to use find() method
        if(item.find(searchInput) != string::npos){ //if we can find the searchInput
                qItem = QString::fromStdString(item); //convert to QString
                results.push_back(qItem); //push onto vector
        }
    }
    return results;
}
