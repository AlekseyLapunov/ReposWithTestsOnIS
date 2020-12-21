#ifndef MYINFOWINDOW_H
#define MYINFOWINDOW_H

#include <QDialog>
#include <DataBases.h>
#include <QStandardItemModel>

namespace Ui {
class MyInfoWindow;
}

class MyInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MyInfoWindow(QWidget *parent = nullptr);
    ~MyInfoWindow();

    void givePassPtr(Passenger *passPtr);
    void giveTicketsListPtr(QList<Ticket>*);
    void fillTable();

private:
    void getListToShow();

    QList<Ticket> ticketsToShow;
    QList<Ticket> *ticketsListPtr;
    Passenger *curPassPtr;
    Ui::MyInfoWindow *ui;
    QStandardItemModel *table;
};

#endif // MYINFOWINDOW_H
