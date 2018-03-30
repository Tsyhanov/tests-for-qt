#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTreeView>

#include "treemodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile file(":/items.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel model(file.readAll());
    file.close();

//    QTreeView view;
    QTreeView* view = new QTreeView;
    view->setModel(&model);
    view->setWindowTitle(QObject::tr("Simple Tree Model"));
    view->show();

//    MainWindow w;
//    w.show();

    return a.exec();
}
