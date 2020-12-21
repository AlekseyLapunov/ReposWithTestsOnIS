#include "MyInfoWindow.h"
#include "ui_MyInfoWindow.h"

MyInfoWindow::MyInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyInfoWindow)
{
    ui->setupUi(this);
    table = new QStandardItemModel(this);
    ui->myTickets->setModel(table);
}

MyInfoWindow::~MyInfoWindow()
{
    ticketsListPtr = nullptr;
    ticketsToShow.clear();
    delete ui;
}

void MyInfoWindow::givePassPtr(Passenger *passPtr)
{
    curPassPtr = passPtr;
}

void MyInfoWindow::giveTicketsListPtr(QList<Ticket> *allTicketsPtr)
{
    ticketsListPtr = allTicketsPtr;
    getListToShow();
}

void MyInfoWindow::getListToShow()
{
    if(ticketsListPtr)
    for(int i = 0; i < (int) ticketsListPtr->size(); i++)
    {
        Ticket temp = ticketsListPtr->at(i);
        if(temp.getPassID() == curPassPtr->getID())
        ticketsToShow.push_back(temp);
    }
}

void MyInfoWindow::fillTable()
{
    if(curPassPtr)
    {
        ui->fullNameLabel->setText(tr("ФИО: %1").arg(curPassPtr->getFullName()));
        ui->loginLabel->setText(tr("Логин: %1").arg(QString::fromStdString(curPassPtr->getLogin())));
        ui->passportLabel->setText(tr("Паспорт: %1").arg(curPassPtr->getPassport()));
    }
    if(ticketsListPtr)
    {
        getListToShow();
        table->setColumnCount(2);
        table->setRowCount(ticketsToShow.size());
        QModelIndex index;
        QStringList collsName = {"ID рейса", "Статус"};
        table->setHorizontalHeaderLabels(collsName);
        for(int row = 0; row < table->rowCount(); row++)
        {
            index = table->index(row, 0);
            table->setData(index, ticketsToShow[row].getRouteID());
            index = table->index(row, 1);
            table->setData(index, ticketsToShow[row].getStatusStr());
        }
    }
}

