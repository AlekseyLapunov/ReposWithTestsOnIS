#include "RoutesBase.h"

RoutesBase::RoutesBase()
{

}

void RoutesBase::createRouteNote(int ID, QString dep, QString des,
                                 QString mark, int seats, QDataStream &qstream)
{
    qstream << ID << dep << des << mark << seats;
}

bool RoutesBase::find(int fID, QString fDep, QString fDes,
                      QString fMark, int fSeats, Route &fRoute)
{
    QFile RoutesBase("Data_Bases/Routes_Base.bin");
    if(RoutesBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&RoutesBase);
        while(!qstream.atEnd())
        {
            int ID, seats; QString dep, des, mark;
            qstream >> ID >> dep >> des >> mark >> seats;
            if((ID == fID) && (dep == fDep) && (des == fDes)
               && (mark == fMark) && (seats == fSeats))
            {
                Route foundRoute(ID, dep, des, mark, seats);
                fRoute = foundRoute;
                return true;
            }
        }
        RoutesBase.close();
    }
    return false;
}

bool RoutesBase::find(int fID, Route &fRoute)
{
    QFile RoutesBase("Data_Bases/Routes_Base.bin");
    if(RoutesBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&RoutesBase);
        while(!qstream.atEnd())
        {
            int ID, seats; QString dep, des, mark;
            qstream >> ID >> dep >> des >> mark >> seats;
            if(ID == fID)
            {
                Route foundRoute(ID, dep, des, mark, seats);
                fRoute = foundRoute;
                return true;
            }
        }
        RoutesBase.close();
    }
    return false;
}

void RoutesBase::refreshBase(QList<Route> &pRouteList)
{
    QFile RoutesBase("Data_Bases/Routes_Base.bin");
    if(RoutesBase.open(QIODevice::WriteOnly))
    {
        QDataStream qstream(&RoutesBase);
        for(int i = 0; i < pRouteList.size(); i++)
        {
            int ID = pRouteList[i].getID(),
                    seats = pRouteList[i].getSeats();

            QString dep = pRouteList[i].getDepart(),
                    des = pRouteList[i].getDest(),
                    mark = pRouteList[i].getMark();

            if(ID != -1)
            {
                createRouteNote(ID, dep, des, mark, seats, qstream);
            }
        }
        RoutesBase.close();
    }
}

void RoutesBase::loadBase(QList<Route> &pRouteList)
{
    pRouteList.clear();
    QFile RoutesBase("Data_Bases/Routes_Base.bin");
    if(RoutesBase.open(QIODevice::ReadOnly))
    {
        QDataStream qstream(&RoutesBase);
        while(!qstream.atEnd())
        {
            int ID, seats; QString dep, des, mark;
            qstream >> ID >> dep >> des >> mark >> seats;
            Route transmitter(ID, dep, des, mark, seats);
            pRouteList.push_back(transmitter);
        }
        RoutesBase.close();
    }
}
