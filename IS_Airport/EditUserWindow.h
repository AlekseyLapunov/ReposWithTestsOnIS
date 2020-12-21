#ifndef EDITUSERWINDOW_H
#define EDITUSERWINDOW_H

#include <QDialog>
#include <User.h>
#include <DataBases.h>

namespace Ui {
class EditUserWindow;
}

class EditUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserWindow(QWidget *parent = nullptr);
    ~EditUserWindow();

    void giveUserPtr(User*);
    void giveCurUserPtr(User*);
    void giveDBManagerPtr(DataBases*);
    void giveBoolPtr(bool *boolPtr);
    void setFields();

private slots:

    void accept() override;

private:
    void checkWarn();
    bool checkFields();
    bool passToOther();
    bool otherToPass();
    bool doesUserChange();
    bool *userChanged;
    DataBases *DBManagerPtr;
    User *userPtr;
    User *curUserPtr;
    Ui::EditUserWindow *ui;
};

#endif // EDITUSERWINDOW_H
