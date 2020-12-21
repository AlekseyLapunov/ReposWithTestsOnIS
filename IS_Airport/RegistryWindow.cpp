#include "RegistryWindow.h"
#include "ui_RegistryWindow.h"

#include <QMessageBox>
#include <QString>
#include <QRegularExpression>

RegistryWindow::RegistryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistryWindow)
{
    ui->setupUi(this);
}

RegistryWindow::~RegistryWindow()
{
    delete ui;
}

void RegistryWindow::giveDBPtr(DataBases *DBPtr)
{
    DBManagePtr = DBPtr;
}

void RegistryWindow::beginRegistry()
{
    if(!checkFields())
    {
        RegistryWindow::warnBox();
    }
    else
    {

        string thisLogin = getLoginFF(), thisPassword = getPasswordFF();
        QString thisFullName = getFullNameFF(), thisPassInfo = getPassportFF();
        QString thisPassport = getPassportFF();
        if(DBManagePtr->loginFound(thisLogin) || DBManagePtr->passFound(thisPassport))
        {
            RegistryWindow::existensBox();
        }
        else
        {
            DBManagePtr->pushUser(thisLogin, thisPassword);
            DBManagePtr->pushPassenger(thisFullName, thisPassInfo);
            QDialog::accept();
            RegistryWindow::gracBox();
        }

    }
}

void RegistryWindow::gracBox()
{
    QMessageBox mBox;
    mBox.setWindowTitle(tr("Поздравляем!"));
    mBox.setIcon(QMessageBox::Information);
    mBox.setText(tr("Регистрация завершена."));
    mBox.exec();
}

void RegistryWindow::warnBox()
{
    QMessageBox mBox;
    mBox.setWindowTitle(tr("Внимание"));
    mBox.setIcon(QMessageBox::Warning);
    mBox.setText(tr("Проверьте введённые данные, пожалуйста"));
    mBox.exec();
}

void RegistryWindow::existensBox()
{
    QMessageBox mBox;
    mBox.setWindowTitle(tr("Внимание"));
    mBox.setIcon(QMessageBox::Warning);
    mBox.setText(tr("Такой пользователь уже зарегистрирован"));
    mBox.exec();
}

bool RegistryWindow::checkFields()
{
    if(anyEmpty()) return false;
    if(checkLoginField() &&
    checkPasswordField() &&
    checkPasswords()     &&
    checkFullNameField() &&
    checkPassportField())
    return true; else return false;
}

bool RegistryWindow::anyEmpty()
{
    if(getLoginFF().length() <= 0 ||
       getPasswordFF().length() <= 0 ||
       getPasswordACKFF().length() <= 0 ||
       getFullNameFF().length() <=0 ||
       getPassportFF().length() <= 0) return true;
    else return false;
}

bool RegistryWindow::checkLoginField()
{
    string login = getLoginFF();
    if(login == "admintools" || login == "root") return false;
    if(login.length() < 4 || login.length() > 12) return false;
    else
    {
        // Посимвольная проверка
        for(int i = 0; i < (int) login.length(); i++)
        {
            int charToInt = login[i];
            if((charToInt < 97 || charToInt > 122) &&
               (charToInt < 48 || charToInt > 57))
                return false;
        }
        return true;
    }
}

bool RegistryWindow::checkPasswordField()
{
    string password = getPasswordFF();
    if(password.length() < 4 || password.length() > 18) return false;
    else
    {
        // Посимвольная проверка
        for(int i = 0; i < (int) password.length(); i++)
        {
            int charToInt = password[i];
            if((charToInt < 65 || charToInt > 90)
               && (charToInt < 97 || charToInt > 122)
               && (charToInt < 48 || charToInt > 57)
               && (charToInt < 35 || charToInt > 38)
               && (charToInt != 42) && (charToInt != 32)
               && (charToInt != 38))
                return false;
        }
        return true;
    }
}

bool RegistryWindow::checkFullNameField()
{
    QString fullName = getFullNameFF();
    if(fullName.size() < 6 || fullName.size() > 40) return false;
    // Если ФИО содержит буквы кроме русских
    if(fullName.contains(QRegularExpression("[^А-Я а-я]")))
        {
            return false;
        }
    if(fullName[0] == " ") return false;
    if(fullName.count(" ") != 2) return false;
    if(fullName.count("  ") != 0) return false;
    return true;
}

bool RegistryWindow::checkPassportField()
{
    QString passInfo = getPassportFF();
    int length = passInfo.length();
    if(length != 11) return false;
    // Если паспортная информация содержит что-то кроме цифр и пробела
    if(passInfo.contains(QRegularExpression("[^0-9 ]")))
        {
            return false;
        }
    if(passInfo.count(" ") != 1) return false;
    return true;
}

bool RegistryWindow::checkPasswords()
{
    if(getPasswordFF() == getPasswordACKFF())
    return true; else return false;
}

string RegistryWindow::getLoginFF()
{
    return this->ui->loginField->text().toStdString();
}

string RegistryWindow::getPasswordFF()
{
    return this->ui->passwordField->text().toStdString();
}

string RegistryWindow::getPasswordACKFF()
{
    return this->ui->passwordField_2->text().toStdString();
}

QString RegistryWindow::getFullNameFF()
{
    return this->ui->fullNameField->text();
}

QString RegistryWindow::getPassportFF()
{
    return this->ui->passportField->text();
}
