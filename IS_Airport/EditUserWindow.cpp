#include "EditUserWindow.h"
#include "ui_EditUserWindow.h"

#include <EditPassWindow.h>
#include <QMessageBox>

EditUserWindow::EditUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserWindow)
{
    ui->setupUi(this);

}

EditUserWindow::~EditUserWindow()
{
    delete ui;
}

void EditUserWindow::giveUserPtr(User *sPtr)
{
    userPtr = sPtr;
}

void EditUserWindow::giveCurUserPtr(User *sPtr)
{
    curUserPtr = sPtr;
}

void EditUserWindow::giveDBManagerPtr(DataBases *sPtr)
{
    DBManagerPtr = sPtr;
}

void EditUserWindow::giveBoolPtr(bool *sBoolPtr)
{
    userChanged = sBoolPtr;
}

void EditUserWindow::accept()
{
    if(checkFields())
    {
        // Поменялись ли данные пользователя вообще
        if(!doesUserChange())
        {
            *userChanged = false;
        }
        else
        {
            // Если делаем из пассажира кассира или администратора
            if(passToOther())
            {
                QMessageBox passBox;
                passBox.setIcon(QMessageBox::Question);
                passBox.setWindowTitle("Вопрос");
                passBox.setText(tr("Вы уверены, что хотите удалить соответствующие<br>"
                                   " записи об этом пассажире и его билетах?<br>"
                                   " Эти данные не смогут быть восстановлены."));
                passBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
                passBox.setDefaultButton(QMessageBox::Yes);
                if(passBox.exec() == QMessageBox::Yes)
                {
                    DBManagerPtr->destroyPassAndTickets(userPtr->getID());
                    *userChanged = true;
                    User transmitter(ui->loginEdit->text().toStdString(),
                                     ui->passwordEdit->text().toStdString(),
                                     userPtr->getID(), ui->typeEdit->currentIndex());
                    *userPtr = transmitter;
                }
            }
            // Если делаем из кассира или администратора пассажира
            else if(otherToPass())
            {
                QMessageBox otherBox;
                otherBox.setIcon(QMessageBox::Question);
                otherBox.setWindowTitle("Вопрос");
                otherBox.setText(tr("Вы собираетесь создать (загистрировать) нового пассажира?"));
                otherBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
                otherBox.setDefaultButton(QMessageBox::Yes);
                if(otherBox.exec() == QMessageBox::Yes)
                {
                    bool passTemp = false;
                    EditPassWindow newPass(this);
                    newPass.setWindowTitle("Новый пассажир");
                    newPass.giveDBManagerPtr(DBManagerPtr);
                    newPass.giveBoolPtr(&passTemp);
                    Passenger pTransm;
                    newPass.givePassPtr(&pTransm);
                    newPass.exec();
                    if(passTemp)
                    {
                        DBManagerPtr->pushPassenger(pTransm.getFullName(), pTransm.getPassport(),
                                                    false, userPtr->getID());
                        *userChanged = true;
                        User transmitter(ui->loginEdit->text().toStdString(),
                                         ui->passwordEdit->text().toStdString(),
                                         userPtr->getID(), ui->typeEdit->currentIndex());
                        *userPtr = transmitter;
                    }
                }
            }
            // Если тип пользователя остаётся неизменным
            else
            {
                *userChanged = true;
                User transmitter(ui->loginEdit->text().toStdString(), ui->passwordEdit->text().toStdString(),
                                 userPtr->getID(), ui->typeEdit->currentIndex());
                *userPtr = transmitter;
            }
            checkWarn();
        }
        QDialog::accept();
    }
}

void EditUserWindow::checkWarn()
{
    if(curUserPtr->getID() == userPtr->getID())
    {
        QMessageBox warn(QMessageBox::Warning, "Внимание", "Вы изменили свои данные.<br> "
                                                           "Изменения придут в силу после следующего входа в систему");
        warn.exec();
    }
}

void EditUserWindow::setFields()
{
    if(userPtr)
    {
        ui->loginEdit->setText(QString::fromStdString(userPtr->getLogin()));
        ui->loginEdit->setDisabled(true);
        ui->passwordEdit->setText(QString::fromStdString(userPtr->getPassword()));
        ui->typeEdit->setCurrentIndex(userPtr->getType());
    }
}

bool EditUserWindow::checkFields()
{
    QMessageBox mBox(this);
    mBox.setWindowTitle(tr("Внимание"));
    mBox.setIcon(QMessageBox::Warning);
    mBox.setText(tr("Проверьте введённые данные, пожалуйста"));
    if(ui->loginEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty())
    {
        mBox.exec();
        return false;
    }
    if(ui->loginEdit->text().length() < 4 || ui->loginEdit->text().length() > 12
    || ui->passwordEdit->text().length() < 4 || ui->passwordEdit->text().length() > 18)
    {
        mBox.exec();
        return false;
    }
    if(ui->loginEdit->text().contains(QRegularExpression("[^a-z0-9]")))
    {
        mBox.exec();
        return false;
    }
    if(ui->typeEdit->currentIndex() == 0)
    {
        mBox.exec();
        return false;
    }
    return true;
}

bool EditUserWindow::passToOther()
{
    if(userPtr->getType() == User::idPassenger &&
      (this->ui->typeEdit->currentIndex() == User::idAdministrator ||
       this->ui->typeEdit->currentIndex() == User::idCashier))
       return true;
       else return false;
}

bool EditUserWindow::otherToPass()
{
    if((userPtr->getType() == User::idAdministrator ||
       userPtr->getType() == User::idCashier) &&
      this->ui->typeEdit->currentIndex() == User::idPassenger)
       return true;
    else return false;
}

bool EditUserWindow::doesUserChange()
{
    if(ui->loginEdit->text() == QString::fromStdString(userPtr->getLogin())
       && ui->passwordEdit->text() == QString::fromStdString(userPtr->getPassword())
       && ui->typeEdit->currentIndex() == userPtr->getType()) return false;
    else return true;
}
