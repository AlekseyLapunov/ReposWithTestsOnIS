#ifndef TICKET_H
#define TICKET_H

#include "QString"

class Ticket
{
private:
    int routeID;
    int passID;
    int status;
public:
    enum {stUndef, stReq, stReqAns, stRet, stRetAns};
    int getRouteID();
    int getPassID();
    int getStatus();
    QString getStatusStr();
    Ticket();
    Ticket(int sRouteID, int sPassID, int sStatus = stReq);
};

#endif // TICKET_H
