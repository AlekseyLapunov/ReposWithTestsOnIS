#ifndef TICKETSBASE_H
#define TICKETSBASE_H

#include <QString>
#include <Ticket.h>
#include <QDataStream>
#include <QList>
#include "QFile"

class TicketsBase
{
public:
    TicketsBase();

    // Создаёт запись в двоичном файле потока qstream
    static void createTicketNote(int routeID, int passID, int status, QDataStream &qstream);

    // Функция находит билет в базе данных
    static bool find(int fRouteID, int fPassID, int fStatus, Ticket &fTicket);
    // Функция находит билет в базе данных
    static bool find(int fRouteID, int fPassID, Ticket &fTicket);

    static void refreshBase(QList<Ticket> &pTicketList);

    static void loadBase(QList<Ticket> &pTicketList);
private:

};

#endif // TICKETSBASE_H
