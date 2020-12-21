#include "TicketsBase.h"

TicketsBase::TicketsBase()
{

}

void TicketsBase::createTicketNote(int sRouteID, int sPassID, int status, QDataStream &qstream)
{
    qstream << sRouteID << sPassID << status;
}

bool TicketsBase::find(int fRouteID, int fPassID, int fStatus, Ticket &fTicket)
{
    QFile TicketsBase("Data_Bases/Tickets_Base.bin");
    if(TicketsBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&TicketsBase);
        while(!qstream.atEnd())
        {
            int routeID, passID, status;
            qstream >> routeID >> passID >> status;
            if((routeID == fRouteID) && (passID == fPassID) && (status == fStatus))
            {
                Ticket foundTicket(routeID, passID, status);
                fTicket = foundTicket;
                return true;
            }
        }
        TicketsBase.close();
    }
    return false;
}

bool TicketsBase::find(int fRouteID, int fPassID, Ticket &fTicket)
{
    QFile TicketsBase("Data_Bases/Tickets_Base.bin");
    if(TicketsBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&TicketsBase);
        while(!qstream.atEnd())
        {
            int routeID, passID, status;
            qstream >> routeID >> passID >> status;
            if((routeID == fRouteID) && (passID == fPassID))
            {
                Ticket foundTicket(routeID, passID, status);
                fTicket = foundTicket;
                return true;
            }
        }
        TicketsBase.close();
    }
    return false;
}

void TicketsBase::refreshBase(QList<Ticket> &pTicketList)
{
    QFile TicketsBase("Data_Bases/Tickets_Base.bin");
    if(TicketsBase.open(QIODevice::WriteOnly))
    {
        QDataStream qstream(&TicketsBase);
        for(int i = 0; i < pTicketList.size(); i++)
        {
            int routeID = pTicketList[i].getRouteID(), passID = pTicketList[i].getPassID(),
                status = pTicketList[i].getStatus();
            if(status != Ticket::stUndef)
            {
                createTicketNote(routeID, passID, status, qstream);
            }
        }
        TicketsBase.close();
    }
}

void TicketsBase::loadBase(QList<Ticket> &pTicketList)
{
    pTicketList.clear();
    QFile TicketsBase("Data_Bases/Tickets_Base.bin");
    if(TicketsBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&TicketsBase);
        while(!qstream.atEnd())
        {
            int routeID, passID, status;
            qstream >> routeID >> passID >> status;
            Ticket transmitter(routeID, passID, status);
            pTicketList.push_back(transmitter);
        }
        TicketsBase.close();
    }
}
