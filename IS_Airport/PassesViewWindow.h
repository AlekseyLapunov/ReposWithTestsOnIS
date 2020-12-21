#ifndef PASSESVIEWWINDOW_H
#define PASSESVIEWWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <DataBases.h>
#include <Passenger.h>
#include <string>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <EditPassWindow.h>

namespace Ui {
class PassesViewWindow;
}

class PassesViewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PassesViewWindow(QWidget *parent = nullptr);
    ~PassesViewWindow();

    void giveDBManagerPtr(DataBases *DBPointer);
    void giveListPtr(QList<Passenger> *sPassListPtr);
    void fillTable(bool def = 1);

private slots:
    void editPass(QModelIndex);
    void startFilter();

private:
    DataBases *DBManagerPtr;

    QList<Passenger> passesToShow;
    QList<Passenger> *passesListPtr;

    void refreshListPtr();

    Passenger passFound;
    bool passChanged;

    EditPassWindow editPassWindow;
    QStandardItemModel *table;

    Ui::PassesViewWindow *ui;

};

#endif // PASSESVIEWWINDOW_H
