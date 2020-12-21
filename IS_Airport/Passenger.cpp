#include "Passenger.h"

Passenger::Passenger()
{
    fullName = "UNDEF UNDEF UNDEF";
    passportInfo = "XXXX YYYYYY";
}

Passenger::Passenger(QString sFullName, string sPassportInfo, int sID)
{
    fullName = sFullName;
    passportInfo = sPassportInfo;
    ID = sID;
    type = idPassenger;
}

QString Passenger::fixFullName(QString sFullName)
{
    setlocale(LC_ALL, "");
    wstring buffer = sFullName.toStdWString();
    bool nextUpper = true;
    for(int i = 0; i < (int) sFullName.length(); i++)
    {
        if(nextUpper)
        {
            buffer[i] =  towupper(buffer[i]);
            nextUpper = false;
        }
        else
        if(sFullName[i] == ' ')
        {
            nextUpper = true;
        }
        else if(!nextUpper)buffer[i] = towlower(buffer[i]);
    }
    return sFullName = QString::fromStdWString(buffer);
}

QString Passenger::getFullName()
{
    return this->fullName;
}

QString Passenger::getPassport()
{
    return QString::fromStdString(passportInfo);
}

void Passenger::setLogin(std::string sLogin)
{
    this->login = sLogin;
}

void Passenger::setPassword(std::string sPassword)
{
    this->password = sPassword;
}
