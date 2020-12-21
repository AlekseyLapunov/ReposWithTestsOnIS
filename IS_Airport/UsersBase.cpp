#include "UsersBase.h"
#include "QFile"
#include "QDataStream"

UsersBase::UsersBase()
{

}

void UsersBase::createUserNote(QString login, QString password, int ID, int type, QDataStream &qstream)
{
    qstream << login << password << ID << type;
}

bool UsersBase::find(string fLogin, string fPassword, User &fUser)
{
    QFile usersBase("Data_Bases/Users_Base.bin");
    if(usersBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&usersBase);
        while(!qstream.atEnd())
        {
            int id, type; QString login; QString password;
            qstream >> login >> password >> id >> type;
            if((login.toStdString() == fLogin) && (password.toStdString() == fPassword))
            {
                User foundUser(login.toStdString(), password.toStdString(), id, type);
                fUser = foundUser;
                return true;
            }
        }
        usersBase.close();
    }
    return false;
}

bool UsersBase::find(int fId, string fLogin, User &fUser)
{
    QFile usersBase("Data_Bases/Users_Base.bin");
    if(usersBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&usersBase);
        while(!qstream.atEnd())
        {
            int id, type; QString login; QString password;
            qstream >> login >> password >> id >> type;
            if(login.toStdString() == fLogin && id == fId)
            {
                User foundUser(login.toStdString(), password.toStdString(), id, type);
                fUser = foundUser;
                return true;
            }
        }
        usersBase.close();
    }
    return false;
}

bool UsersBase::find(string fLogin, User &fUser)
{
    QFile usersBase("Data_Bases/Users_Base.bin");
    if(usersBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&usersBase);
        while(!qstream.atEnd())
        {
            int id, type; QString login; QString password;
            qstream >> login >> password >> id >> type;
            if(login.toStdString() == fLogin)
            {
                User foundUser(login.toStdString(), password.toStdString(), id, type);
                fUser = foundUser;
                return true;
            }
        }
        usersBase.close();
    }
    return false;
}

bool UsersBase::find(string fLogin)
{
    QFile usersBase("Data_Bases/Users_Base.bin");
    if(usersBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&usersBase);
        while(!qstream.atEnd())
        {
            int id, type; QString login; QString password;
            qstream >> login >> password >> id >> type;
            if(login.toStdString() == fLogin)
            {
                return true;
            }
        }
        usersBase.close();
    }
    return false;
}

void UsersBase::refreshBase(QList<User> &pUserList)
{
    QFile usersBase("Data_Bases/Users_Base.bin");
    if(usersBase.open(QIODevice::WriteOnly))
    {
        QDataStream qstream(&usersBase);
        for(int i = 0; i < pUserList.size(); i++)
        {
            int ID = pUserList[i].getID(), type = pUserList[i].getType();
            if(ID != -1)
            {
                QString login = QString::fromStdString(pUserList[i].getLogin());
                QString password = QString::fromStdString(pUserList[i].getPassword());
                createUserNote(login, password, ID, type, qstream);
            }
        }
        usersBase.close();
    }
}

void UsersBase::loadBase(QList<User> &pUserList)
{
    pUserList.clear();
    QFile usersBase("Data_Bases/Users_Base.bin");
    if(usersBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&usersBase);
        while(!qstream.atEnd())
        {
            int id, type; QString login; QString password;
            qstream >> login >> password >> id >> type;
            User transmitter(login.toStdString(), password.toStdString(), id, type);
            pUserList.push_back(transmitter);
        }
        usersBase.close();
    }
}










