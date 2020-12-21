#ifndef MANAGEROUTESWINDOW_H
#define MANAGEROUTESWINDOW_H

#include <QWidget>
#include <DataBases.h>
#include <QString>
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class ManageRoutesWindow;
}

class ManageRoutesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageRoutesWindow(QWidget *parent = nullptr);
    ~ManageRoutesWindow();

    void giveDBPtr(DataBases *DBPtr);

private slots:

    void deleteRoute();
    void createRoute();
    void reactToCheck();

private:
    enum{creating, deleting};

    void setShowMode(bool);
    void gracBox(int);
    void existensBox(int);
    void warnBox();
    void critBox();
    bool checkFields(int);

    bool checkIDEdit();
    bool checkDepDesEdits();
    bool checkMarkEdit();
    bool checkSeatsEdit();
    DataBases *DBManagePtr;

    Route foundRoute;

    Ui::ManageRoutesWindow *ui;
};

#endif // MANAGEROUTESWINDOW_H
