#include "RoutesViewWindow.h"
#include "ui_RoutesViewWindow.h"
#include <QMessageBox>

RoutesViewWindow::RoutesViewWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoutesViewWindow)
{
    ui->setupUi(this);
    table = new QStandardItemModel(this);
    ui->routesView->setModel(table);
}

RoutesViewWindow::~RoutesViewWindow()
{
    DBManagerPtr = nullptr;
    routesListPtr = nullptr;
    routesToShow.clear();
    delete ui;
}

void RoutesViewWindow::giveDBManagerPtr(DataBases *DBPointer)
{
    DBManagerPtr = DBPointer;
}

void RoutesViewWindow::giveListPtr(QList<Route> *sRouteListPtr)
{
    routesListPtr = sRouteListPtr;
}

void RoutesViewWindow::refreshListPtr()
{
    routesToShow = *routesListPtr;
}

void RoutesViewWindow::fillTable(bool def)
{
    if(def) refreshListPtr();
    table->setColumnCount(5);
    table->setRowCount(routesToShow.size());
    QModelIndex index;
    QStringList collsName = {"ID", "П. отправления", "П. назначения",
                             "Марка с.", "Кол-во св. мест"};
    table->setHorizontalHeaderLabels(collsName);
    for(int row = 0; row < table->rowCount(); row++)
    {
        index = table->index(row, 0);
        table->setData(index, routesToShow[row].getID());
        index = table->index(row, 1);
        table->setData(index, routesToShow[row].getDepart());
        index = table->index(row, 2);
        table->setData(index, routesToShow[row].getDest());
        index = table->index(row, 3);
        table->setData(index, routesToShow[row].getMark());
        index = table->index(row, 4);
        table->setData(index, routesToShow[row].getSeats());
    }
}

void RoutesViewWindow::startFilter()
{
    routesToShow.clear();
    for(int i = 0; i < (int) routesListPtr->size(); i++)
    {
        Route temp = routesListPtr->at(i);
        QString dep = ui->depFilter->text(); QString des = ui->desFilter->text();
        if(temp.getDepart().count(dep) != 0 && temp.getDest().count(des) != 0)
            routesToShow.push_back(temp);
    }
    fillTable(0);
}
