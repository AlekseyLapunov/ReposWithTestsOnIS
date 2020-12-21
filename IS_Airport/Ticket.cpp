#include "Ticket.h"

Ticket::Ticket()
{
    routeID = -1;
    passID = -1;
    status = stUndef;
}

Ticket::Ticket(int sRouteID, int sPassID, int sStatus)
{
    this->routeID = sRouteID; this->passID = sPassID;
    this->status = sStatus;
}

int Ticket::getRouteID()
{
    return routeID;
}

int Ticket::getPassID()
{
    return passID;
}

int Ticket::getStatus()
{
    return status;
}

QString Ticket::getStatusStr()
{
    if(this->status == stReq) return "Покупка";
    else if(this->status == stReqAns) return "Куплен";
    else if(this->status == stRet) return "Возврат";
    else if(this->status == stRetAns) return "Возвращён";
    else return "НЕ ОПРЕД.";
}


