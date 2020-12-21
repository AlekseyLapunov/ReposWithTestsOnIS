#include "PassengersBase.h"
#include <QFile>

PassengersBase::PassengersBase()
{

}

void PassengersBase::createPassNote(QString fullName, QString passport, int ID, QDataStream &qstream)
{
    qstream << fullName << passport << ID;
}

bool PassengersBase::find(QString fFullName, QString fPassport, Passenger &fPassenger)
{
    QFile passBase("Data_Bases/Passengers_Base.bin");
    if(passBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&passBase);
        while(!qstream.atEnd())
        {
            QString fullName; QString passport; int ID;
            qstream >> fullName >> passport >> ID;
            if((fullName == fFullName) && (passport == fPassport))
            {
                Passenger foundPass(fullName, passport.toStdString(), ID);
                fPassenger = foundPass;
                return true;
            }
        }
        passBase.close();
    }
    return false;
}

bool PassengersBase::find(int id, Passenger &ptr)
{
    QFile passBase("Data_Bases/Passengers_Base.bin");
    if(passBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&passBase);
        while(!qstream.atEnd())
        {
            QString fullName; QString passport; int ID;
            qstream >> fullName >> passport >> ID;
            if(ID == id)
            {
                Passenger transmitter(fullName, passport.toStdString(), ID);
                ptr = transmitter;
                return true;
            }
        }
        passBase.close();
    }
    return false;
}

bool PassengersBase::find(string passportCombination)
{
    QFile passBase("Data_Bases/Passengers_Base.bin");
    if(passBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&passBase);
        while(!qstream.atEnd())
        {
            QString fullName; QString passport; int ID;
            qstream >> fullName >> passport >> ID;
            if(passport.toStdString() == passportCombination)
            {
                return true;
            }
        }
        passBase.close();
    }
    return false;
}

void PassengersBase::refreshBase(QList<Passenger> &pPassList)
{
    QFile passBase("Data_Bases/Passengers_Base.bin");
    if(passBase.open(QIODevice::WriteOnly))
    {
        QDataStream qstream(&passBase);
        for(int i = 0; i < pPassList.size(); i++)
        {
            QString fullName = pPassList[i].getFullName();
            QString passport = pPassList[i].getPassport();
            int ID = pPassList[i].getID();
            createPassNote(fullName, passport, ID, qstream);
        }
        passBase.close();
    }
}

void PassengersBase::loadBase(QList<Passenger> &pPassList)
{
    pPassList.clear();
    QFile passBase("Data_Bases/Passengers_Base.bin");
    if(passBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&passBase);
        while(!qstream.atEnd())
        {
            int ID; QString fullName; QString passport;
            qstream >> fullName >> passport >> ID;
            Passenger transmitter(fullName, passport.toStdString(), ID);
            pPassList.push_back(transmitter);
        }
        passBase.close();
    }
}

