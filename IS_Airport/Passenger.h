#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include "User.h"
#include <QString>

class Passenger : public User
{
private:

QString fullName;
string passportInfo;

public:


    Passenger();
    Passenger(QString sFullName, string sPassportInfo, int ID);

    static QString fixFullName(QString sFullName);

    QString getFullName();
    QString getPassport();

    void setLogin(std::string);
    void setPassword(std::string);
};

#endif // PASSENGER_H
