#ifndef EDITPASSWINDOW_H
#define EDITPASSWINDOW_H

#include <QDialog>
#include <Passenger.h>
#include <DataBases.h>

namespace Ui {
class EditPassWindow;
}

class EditPassWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditPassWindow(QWidget *parent = nullptr);
    ~EditPassWindow();

    void givePassPtr(Passenger*);
    void giveDBManagerPtr(DataBases*);
    void giveBoolPtr(bool *boolPtr);
    void setFields();

private slots:

    void accept() override;

private:
    bool checkFields();

    bool *passChanged;
    DataBases *DBManagerPtr;
    Passenger *passPtr;

    Ui::EditPassWindow *ui;
};

#endif // EDITPASSWINDOW_H
