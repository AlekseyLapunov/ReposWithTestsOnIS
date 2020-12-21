#ifndef PASSENGERSBASE_H
#define PASSENGERSBASE_H

#include <Passenger.h>
#include <QList>
#include <QDataStream>

class PassengersBase
{
public:
    PassengersBase();

    // Создаёт запись в двоичном файле потока qstream
    static void createPassNote(QString fullName, QString passport, int ID, QDataStream &qstream);

    // Функция находит пассажира в базе данных
    static bool find(QString fullName, QString passport, Passenger &fPassenger);

    static bool find(int id, Passenger &ptr);

    // Функция находит комбинацию серии и номера паспорта в базе данных
    static bool find(string passportCombination);

    static void refreshBase(QList<Passenger> &pPassList);

    static void loadBase(QList<Passenger> &pPassList);
};

#endif // PASSENGERSBASE_H
