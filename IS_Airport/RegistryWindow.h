#ifndef REGISTRYWINDOW_H
#define REGISTRYWINDOW_H

#include <QDialog>
#include <string>
#include <DataBases.h>

using namespace std;

namespace Ui {
class RegistryWindow;
}

class RegistryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistryWindow(QWidget *parent = nullptr);
    ~RegistryWindow();

    void giveDBPtr(DataBases *DBPtr);

private slots:
    void beginRegistry();

private:
    bool checkFields();
    bool checkPasswords();
    bool checkLoginField();
    bool checkPasswordField();
    bool checkFullNameField();
    bool checkPassportField();
    bool anyEmpty();

    void gracBox();
    void warnBox();
    void existensBox();

    string getLoginFF();
    string getPasswordFF();
    string getPasswordACKFF();
    QString getFullNameFF();
    QString getPassportFF();

    DataBases *DBManagePtr;
    Ui::RegistryWindow *ui;
};

#endif // REGISTRYWINDOW_H
