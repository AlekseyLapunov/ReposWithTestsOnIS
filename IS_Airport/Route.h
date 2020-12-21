#ifndef ROUTE_H
#define ROUTE_H

#include <QString>

class Route
{
private:
    int ID;
    QString departure;
    QString destination;
    QString mark;
    int seats;
public:
    Route();
    Route(int sID, QString sDep, QString sDes,
          QString sMark, int sSeats);
    int getID();
    QString getDepart();
    QString getDest();
    QString getMark();
    int getSeats();
};

#endif // ROUTE_H
