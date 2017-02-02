//This header file sets up the mainwindow.cpp and .ui files
//Contains slots to connect the widgets to actions and other objects
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots: //these connect buttons to actions
    void on_goButton_clicked();

    void on_clearButton_clicked();

    void on_searchButton_clicked();

    void on_browserButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
