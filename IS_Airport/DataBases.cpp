#include "DataBases.h"

DataBases::DataBases()
{

}

void DataBases::checkForDir()
{
    QDir dataBasesFolder;
    if(!dataBasesFolder.exists("Data_Bases"))
    {
        dataBasesFolder.mkdir("Data_Bases");
        createHintFile();
        return;
    }
    else return;
}

bool DataBases::find(string login, string password, User &ptr)
{
    if(UsersBase::find(login, password, ptr)) return true;
    else return false;
}

bool DataBases::find(int id, Passenger &ptr)
{
    if(PassengersBase::find(id, ptr)) return true;
    else return false;
}

bool DataBases::find(int id, string login, User &ptr)
{
    if(UsersBase::find(id, login, ptr)) return true;
    else return false;
}

bool DataBases::find(int routeID, int passID, int status, Ticket &ptr)
{
    if(TicketsBase::find(routeID, passID, status, ptr)) return true;
    else return false;
}

bool DataBases::find(int routeID, int passID, Ticket &ptr)
{
    if(TicketsBase::find(routeID, passID, ptr)) return true;
    else return false;
}

bool DataBases::find(int fID, QString fDep, QString fDes, QString fMark, int fSeats, Route &ptr)
{
    if(RoutesBase::find(fID, fDep, fDes, fMark, fSeats, ptr)) return true;
    else return false;
}

bool DataBases::find(int fID, Route &ptr)
{
    if(RoutesBase::find(fID, ptr)) return true;
    else return false;
}

bool DataBases::find(string login, User &ptr)
{
    if(UsersBase::find(login, ptr)) return true;
    else return false;
}

bool DataBases::passFound(QString passInfo)
{
    if(PassengersBase::find(passInfo.toStdString())) return true;
    else return false;
}

bool DataBases::changeUserInfo(int cID, string cLogin, string cPassword, int cType)
{
    for(int i = 0; i < (int)pUserList->size(); i++)
    {
        User temp = pUserList->at(i);
        if(temp.getID() == cID && temp.getLogin() == cLogin)
        {
            User changeBy(cLogin, cPassword, cID, cType);
            pUserList->removeAt(i);
            pUserList->insert(i, changeBy);
            UsersBase::refreshBase(*pUserList);
            return true;
        }
    }
    return false;
}

bool DataBases::changePassInfo(int cID, QString cFullName, string cPassport)
{
    for(int i = 0; i < (int)pPassList->size(); i++)
    {
        Passenger temp = pPassList->at(i);
        if(temp.getID() == cID)
        {
            Passenger changeBy(cFullName, cPassport, cID);
            pPassList->removeAt(i);
            pPassList->insert(i, changeBy);
            PassengersBase::refreshBase(*pPassList);
            return true;
        }
    }
    return false;
}

bool DataBases::changeTicket(int cRouteID, int cPassID, int cStatus)
{
    for(int i = 0; i < (int)pTicketsList->size(); i++)
    {
        Ticket temp = pTicketsList->at(i);
        if(temp.getRouteID() == cRouteID && temp.getPassID() == cPassID)
        {
            Ticket changeBy(cRouteID, cPassID, cStatus);
            pTicketsList->removeAt(i);
            pTicketsList->insert(i, changeBy);
            TicketsBase::refreshBase(*pTicketsList);
            return true;
        }
    }
    return false;
}

void DataBases::createAdmin(string sLogin, string sPassword)
{
    UsersBase::loadBase(*pUserList);

    int sID = pUserList->size() + 1;

    User transmitter(sLogin, sPassword, sID, User::idAdministrator);
    pUserList->push_back(transmitter);

    UsersBase::refreshBase(*pUserList);
}

bool DataBases::loginFound(string login)
{
    if(UsersBase::find(login)) return true; else return false;
}

void DataBases::pushUser(string sLogin, string sPassword)
{
    UsersBase::loadBase(*pUserList);

    int sID = pUserList->size() + 1;

    User transmitter(sLogin, sPassword, sID);
    pUserList->push_back(transmitter);

    UsersBase::refreshBase(*pUserList);
}

void DataBases::pushPassenger(QString sFullName, QString sPassportInfo,
                              bool ifDefault, int uID)
{
    PassengersBase::loadBase(*pPassList);

    int sID = -1;
    if(ifDefault) sID = pUserList->size();
    else sID = uID;

    sFullName = Passenger::fixFullName(sFullName);

    Passenger transmitter(sFullName, sPassportInfo.toStdString(), sID);
    pPassList->push_back(transmitter);

    PassengersBase::refreshBase(*pPassList);
}

void DataBases::pushTicket(int routeID, int passID, int status)
{
    TicketsBase::loadBase(*pTicketsList);

    Ticket transmitter(routeID, passID, status);
    pTicketsList->push_back(transmitter);

    TicketsBase::refreshBase(*pTicketsList);
}

void DataBases::pushRoute(int ID, QString dep, QString des, QString mark, int seats)
{
    RoutesBase::loadBase(*pRoutesList);

    Route transmitter(ID, dep, des, mark, seats);
    pRoutesList->push_back(transmitter);

    RoutesBase::refreshBase(*pRoutesList);
}

void DataBases::changeRouteSeats(int routeID, int nSeats)
{
    for(int i = 0; i < (int)pRoutesList->size(); i++)
    {
        Route temp = pRoutesList->at(i);
        if(temp.getID() == routeID)
        {
            int setSeats = temp.getSeats() + nSeats;
            Route changeBy(routeID, temp.getDepart(), temp.getDest(), temp.getMark(), setSeats);
            pRoutesList->removeAt(i);
            pRoutesList->insert(i, changeBy);
            RoutesBase::refreshBase(*pRoutesList);
            return;
        }
    }
}

bool DataBases::deleteRoute(int rID)
{
    RoutesBase::loadBase(*pRoutesList);

    for(int i = 0; i < (int)pRoutesList->size(); i++)
    {
        Route temp = pRoutesList->at(i);
        if(temp.getID() == rID)
        {
            pRoutesList->removeAt(i);
            RoutesBase::refreshBase(*pRoutesList);
            return true;
        }
    }
    return false;
}

bool DataBases::deleteTicket(int fRouteID, int fPassID)
{
    for(int i = 0; i < (int)pTicketsList->size(); i++)
    {
        Ticket temp = pTicketsList->at(i);
        if(temp.getRouteID() == fRouteID && temp.getPassID() == fPassID)
        {
            pTicketsList->removeAt(i);
            TicketsBase::refreshBase(*pTicketsList);
            return true;
        }
    }
    return false;
}

void DataBases::destroyPassAndTickets(int pID)
{
    PassengersBase::loadBase(*pPassList);
    for(int i = 0; i < (int)pPassList->size(); i++)
    {
        Passenger temp = pPassList->at(i);
        if(temp.getID() == pID)
        {
            pPassList->removeAt(i);
            PassengersBase::refreshBase(*pPassList);
            break;
        }
    }
    TicketsBase::loadBase(*pTicketsList);
    for(int i = (int)pTicketsList->size() - 1; i >= 0; i--)
    {
        Ticket temp = pTicketsList->at(i);
        if(temp.getPassID() == pID)
        {
            pTicketsList->removeAt(i);
        }
    }
    TicketsBase::refreshBase(*pTicketsList);
}

void DataBases::loadAllBase()
{
    UsersBase::loadBase(*pUserList);
    PassengersBase::loadBase(*pPassList);
    TicketsBase::loadBase(*pTicketsList);
    RoutesBase::loadBase(*pRoutesList);
}

void DataBases::setListPointers(QList<User> *users, QList<Passenger> *passes, QList<Route> *routes, QList<Ticket> *tickets)
{
    pUserList = users;
    pPassList = passes;
    pRoutesList = routes;
    pTicketsList = tickets;
}

void DataBases::setPassData(int userID, Passenger &pass)
{
    for(int i = 0; i < (int) pUserList->size(); i++)
    {
        User temp = pUserList->at(i);
        if(temp.getID() == userID)
        {
            pass.setLogin(temp.getLogin());
            pass.setPassword(temp.getPassword());
            return;
        }
    }
}

void DataBases::createHintFile()
{
    QFile hint("Data_Bases/hint.txt");
    if (hint.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        hint.write("Чтобы создать корневого администратора, заполните поля следующим образом:\n"
                   "admintools\n"
                   "30112020\n"
                   "(Используйте окно авторизации)");
        hint.close();
    }
}














