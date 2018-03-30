#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fabric.cpp"
#include "iostream"
#include <QDebug>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    std::vector <RailObj*> v;

    v.push_back(RailObj::createRailObj(Point_ID));
    v.push_back(RailObj::createRailObj(Signal_ID));
    v[0]->info();
    v[1]->info();

}

MainWindow::~MainWindow()
{
    delete ui;
}
