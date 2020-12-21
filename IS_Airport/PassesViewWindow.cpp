#include "PassesViewWindow.h"
#include "ui_PassesViewWindow.h"

PassesViewWindow::PassesViewWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassesViewWindow)
{
    ui->setupUi(this);table = new QStandardItemModel(this);
    ui->passesView->setModel(table);
}

PassesViewWindow::~PassesViewWindow()
{
    DBManagerPtr = nullptr;
    passesListPtr = nullptr;
    passesToShow.clear();
    delete ui;
}

void PassesViewWindow::giveDBManagerPtr(DataBases *DBPointer)
{
    DBManagerPtr = DBPointer;
}

void PassesViewWindow::giveListPtr(QList<Passenger> *sPassesListPtr)
{
    passesListPtr = sPassesListPtr;
}

void PassesViewWindow::refreshListPtr()
{
    passesToShow = *passesListPtr;
}

void PassesViewWindow::fillTable(bool def)
{
    if(def) refreshListPtr();
    table->setColumnCount(3);
    table->setRowCount(passesToShow.size());
    QModelIndex index;
    QStringList collsName = {"ID", "ФИО", "Серия Номер"};
    table->setHorizontalHeaderLabels(collsName);
    for(int row = 0; row < table->rowCount(); row++)
    {
        index = table->index(row, 0);
        table->setData(index, passesToShow[row].getID());
        index = table->index(row, 1);
        table->setData(index, passesToShow[row].getFullName());
        index = table->index(row, 2);
        table->setData(index, passesToShow[row].getPassport());
    }
}

void PassesViewWindow::editPass(QModelIndex index)
{
    int curRowNumber = index.row();
    passChanged = false;
    QModelIndex temp = table->index(curRowNumber, 0);
    int ID = table->data(temp).toInt();
    DBManagerPtr->find(ID, passFound);
    editPassWindow.givePassPtr(&passFound);
    editPassWindow.giveDBManagerPtr(DBManagerPtr);
    editPassWindow.giveBoolPtr(&passChanged);
    editPassWindow.setFields();
    editPassWindow.exec();
    if(passChanged)
    {
        QString sFullName = passFound.getFullName();
        string sPassport = passFound.getPassport().toStdString();
        DBManagerPtr->changePassInfo(ID, sFullName, sPassport);
        fillTable();
    }
}

void PassesViewWindow::startFilter()
{
    passesToShow.clear();
    for(int i = 0; i < (int) passesListPtr->size(); i++)
    {
        Passenger temp = passesListPtr->at(i);
        QString fullName = ui->fullNameFilter->text();
        if(temp.getFullName().count(fullName) != 0)
            passesToShow.push_back(temp);
    }
    fillTable(0);
}
