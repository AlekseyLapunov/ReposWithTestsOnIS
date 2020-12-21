#include "ManageRoutesWindow.h"
#include "ui_ManageRoutesWindow.h"

#include <QRegularExpression>
#include <QDialog>

ManageRoutesWindow::ManageRoutesWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageRoutesWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Управление рейсами");
    this->reactToCheck();
}

ManageRoutesWindow::~ManageRoutesWindow()
{
    delete ui;
}

void ManageRoutesWindow::giveDBPtr(DataBases *DBPtr)
{
    DBManagePtr = DBPtr;
}

void ManageRoutesWindow::deleteRoute()
{
    if(ui->deleteButton->isEnabled())
    {
        if(checkFields(deleting))
        {
            QMessageBox deletingRoute(this);
            deletingRoute.setIcon(QMessageBox::Question);
            deletingRoute.setWindowTitle("Удаление рейса");
            deletingRoute.setText(tr("Вы уверены, что хотите<br> удалить данный рейс?"));
            deletingRoute.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
            deletingRoute.setDefaultButton(QMessageBox::Yes);
            if(deletingRoute.exec() == QMessageBox::Yes)
            {
                if(DBManagePtr->find(ui->idEdit->value(), foundRoute))
                {
                    if(DBManagePtr->deleteRoute(ui->idEdit->value())) gracBox(deleting);
                    else critBox();
                } else existensBox(deleting);
            }
        }
        else warnBox();
    }
}

void ManageRoutesWindow::createRoute()
{
    if(ui->createButton->isEnabled())
    {
        if(checkFields(creating))
        {
            if(!DBManagePtr->find(ui->idEdit->value(), foundRoute))
            {
                int sID = ui->idEdit->value(), seats = ui->seatsEdit->value();
                QString sDep = ui->depEdit->text(), sDes = ui->desEdit->text(),
                sMark = ui->markEdit->text();
                DBManagePtr->pushRoute(sID, sDep, sDes, sMark, seats);
                gracBox(creating);
            }
            else existensBox(creating);
        }
        else warnBox();
    }
}

void ManageRoutesWindow::reactToCheck()
{
    setShowMode(ui->checkBox->isChecked());
}

void ManageRoutesWindow::setShowMode(bool flag)
{
    ui->deleteButton->setEnabled(flag);
    ui->createButton->setDisabled(flag);
    ui->depEdit->setDisabled(flag);
    ui->desEdit->setDisabled(flag);
    ui->markEdit->setDisabled(flag);
    ui->seatsEdit->setDisabled(flag);
    ui->label_2->setDisabled(flag);
    ui->label_3->setDisabled(flag);
    ui->label_4->setDisabled(flag);
    ui->label_5->setDisabled(flag);
}

void ManageRoutesWindow::gracBox(int flag)
{
    QMessageBox mBox(this);
    mBox.setWindowTitle(tr("Поздравляем!"));
    mBox.setIcon(QMessageBox::Information);
    if(flag == creating) mBox.setText(tr("Маршрут успешно создан."));
    else mBox.setText(tr("Маршрут успешно удалён."));
    mBox.exec();
}

void ManageRoutesWindow::existensBox(int flag)
{
    QMessageBox mBox(this);
    mBox.setWindowTitle(tr("Внимание"));
    mBox.setIcon(QMessageBox::Warning);
    if(flag == creating) mBox.setText(tr("Маршрут с таким ID уже создан"));
    else mBox.setText(tr("Маршрут с таким ID отсутствует в базе данных"));
    mBox.exec();
}

void ManageRoutesWindow::warnBox()
{
    QMessageBox mBox(this);
    mBox.setWindowTitle(tr("Внимание"));
    mBox.setIcon(QMessageBox::Warning);
    mBox.setText(tr("Проверьте введённые данные, пожалуйста"));
    mBox.exec();
}

void ManageRoutesWindow::critBox()
{
    QMessageBox mBox(this);
    mBox.setWindowTitle(tr("Ошибка"));
    mBox.setIcon(QMessageBox::Critical);
    mBox.setText(tr("Удаление маршрута не удалось"));
    mBox.exec();
}

bool ManageRoutesWindow::checkFields(int flag)
{
    if(flag == creating)
    {
        if(!checkIDEdit() || !checkDepDesEdits()
                || !checkMarkEdit() || !checkSeatsEdit())
        {
            return false;
        }
    }
    else
    {
        if(!checkIDEdit())
        {
            return false;
        }

    }
    return true;
}

bool ManageRoutesWindow::checkIDEdit()
{
    if(ui->idEdit->value() < 1
            || ui->idEdit->value() > 9999)
    return false;
    else return true;
}

bool ManageRoutesWindow::checkDepDesEdits()
{
    QString dep = ui->depEdit->text();
    QString des = ui->desEdit->text();
    if(dep.size() < 2 || dep.size() > 40) return false;
    if(des.size() < 2 || des.size() > 40) return false;
    if(dep[0] == " " || dep[dep.size() - 1] == " ") return false;
    if(des[0] == " " || des[des.size() - 1] == " ") return false;
    if(dep.count("  ") != 0) return false;
    if(des.count("  ") != 0) return false;
    return true;
}

bool ManageRoutesWindow::checkMarkEdit()
{
    QString mark = ui->markEdit->text();
    if(mark.size() < 1 || mark.size() > 8) return false;
    if(mark.contains(QRegularExpression("[^A-Z0-9]")))
        {
            return false;
        }
    if(mark[0] == " " || mark[mark.size() - 1] == " ") return false;
    if(mark.count("  ") != 0) return false;
    return true;
}

bool ManageRoutesWindow::checkSeatsEdit()
{
    if(ui->seatsEdit->value() < 1
            || ui->seatsEdit->value() > 200)
    return false;
    else return true;
}




