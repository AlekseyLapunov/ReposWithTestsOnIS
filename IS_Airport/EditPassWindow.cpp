#include "EditPassWindow.h"
#include "ui_EditPassWindow.h"
#include <QMessageBox>
#include <QRegularExpression>

EditPassWindow::EditPassWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPassWindow)
{
    ui->setupUi(this);
}

EditPassWindow::~EditPassWindow()
{
    delete ui;
}

void EditPassWindow::givePassPtr(Passenger *sPtr)
{
    passPtr = sPtr;
}

void EditPassWindow::giveDBManagerPtr(DataBases *sPtr)
{
    DBManagerPtr = sPtr;
}

void EditPassWindow::giveBoolPtr(bool *sBoolPtr)
{
    passChanged = sBoolPtr;
}

void EditPassWindow::accept()
{
    if(checkFields())
    {
        if(!DBManagerPtr->passFound(ui->passportEdit->text())
           || passPtr->getPassport() == ui->passportEdit->text())
        {
            *passChanged = true;
            Passenger transmitter(ui->fullNameEdit->text(), ui->passportEdit->text().toStdString(),
                     passPtr->getID());
            *passPtr = transmitter;
            QDialog::accept();
        }
        else
        {
            QMessageBox warnBox(QMessageBox::Warning, "Внимание", "Пассажир с такими данными паспорта уже существует");
            warnBox.exec();
        }
    }
}

void EditPassWindow::setFields()
{
    if(passPtr)
    {
        ui->fullNameEdit->setText(passPtr->getFullName());
        ui->passportEdit->setText(passPtr->getPassport());
    }
}

bool EditPassWindow::checkFields()
{
    QMessageBox mBox(this);
    mBox.setWindowTitle(tr("Внимание"));
    mBox.setIcon(QMessageBox::Warning);
    mBox.setText(tr("Проверьте введённые данные, пожалуйста"));
    if(ui->fullNameEdit->text().isEmpty() || ui->passportEdit->text().isEmpty())
    {
        mBox.exec();
        return false;
    }

    if(ui->fullNameEdit->text().size() < 6 || ui->fullNameEdit->text().size() > 40) return false;
    // Если ФИО содержит буквы кроме русских
    if(ui->fullNameEdit->text().contains(QRegularExpression("[^А-Я а-я]")))
    {
        mBox.exec();
        return false;
    }
    if(ui->fullNameEdit->text().count(" ") != 2)
    {
        mBox.exec();
        return false;
    }
    if(ui->fullNameEdit->text().count("  ") != 0)
    {
        mBox.exec();
        return false;
    }
    int length = ui->passportEdit->text().length();
    if(length != 11)
    {
        mBox.exec();
        return false;
    }
    // Если паспортная информация содержит что-то кроме цифр и пробела
    if(ui->passportEdit->text().contains(QRegularExpression("[^0-9 ]")))
    {
        mBox.exec();
        return false;
    }
    if(ui->passportEdit->text().count(" ") != 1)
    {
        mBox.exec();
        return false;
    }

    return true;
}
