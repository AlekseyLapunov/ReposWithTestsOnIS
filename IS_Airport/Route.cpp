#include "Route.h"

Route::Route()
{
    ID = -1;
    departure = "DEP UNDEF";
    destination = "DES UNDEF";
    mark = "MARK UNDEF";
    seats = -1;
}

Route::Route(int sID, QString sDep, QString sDes,
             QString sMark, int sSeats)
{
    ID = sID; departure = sDep;
    destination = sDes; mark = sMark;
    seats = sSeats;
}

int Route::getID()
{
    return ID;
}

QString Route::getDepart()
{
    return departure;
}

QString Route::getDest()
{
    return destination;
}

QString Route::getMark()
{
    return mark;
}

int Route::getSeats()
{
    return seats;
}


