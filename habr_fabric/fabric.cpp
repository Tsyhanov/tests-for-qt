#include <QDebug>
#include <string>
//#include "mainwindow.h"


enum RailObj_ID {Point_ID=0, Signal_ID};

class RailObj{
public:
    virtual void info() = 0;
    virtual ~RailObj(){};
    static RailObj* createRailObj(RailObj_ID id);

};

class Point: public RailObj{
public:
    void info(){
        qDebug() << "Point class info";
    }
};


class Signal: public RailObj{
public:
    void info(){
        qDebug() << "Signal class info";
    }
};

// Реализация параметризированного фабричного метода
RailObj* RailObj::createRailObj(RailObj_ID id){

    RailObj * p;
    switch(id)
    {
        case Point_ID:
            p = new Point();
            break;
        case Signal_ID:
            p = new Signal();
            break;
        default:
        break;
    }
    return p;
}
