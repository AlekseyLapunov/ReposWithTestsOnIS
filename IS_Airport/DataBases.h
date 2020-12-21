#ifndef DATABASES_H
#define DATABASES_H

#include <User.h>
#include <Passenger.h>
#include <Route.h>
#include <Ticket.h>
#include <QDir>
#include <string>
#include <UsersBase.h>
#include <PassengersBase.h>
#include <RoutesBase.h>
#include <TicketsBase.h>
#include <QList>

class DataBases
{
public:
    DataBases();
    // Проверяет наличие папки базы данных
    static void checkForDir();

    bool find(string login, string password, User &ptr);
    bool find(int id, Passenger &ptr);
    bool find(int id, string login, User &ptr);
    bool find(int routeID, int passID, int status, Ticket &ptr);
    bool find(int routeID, int passID, Ticket &ptr);
    bool find(int ID, QString dep, QString des,
              QString mark, int seats, Route &ptr);
    bool find(int ID, Route &ptr);
    bool find(string login, User &ptr);

    bool loginFound(string login);
    bool passFound(QString passInfo);

    bool changeUserInfo(int cID, string cLogin, string cPassword, int cType);
    bool changePassInfo(int cID, QString cFullName, string cPassport);

    void createAdmin(string sLogin, string sPassword);
    void pushUser(string sLogin, string sPassword);
    void pushPassenger(QString fullName, QString passInfo, bool ifDefault = true, int uID = -1);
    void pushTicket(int routeID, int passID, int status);
    void pushRoute(int ID, QString dep, QString des,
                   QString mark, int seats);
    void changeRouteSeats(int routeID, int nSeats);
    bool deleteRoute(int rID);
    bool deleteTicket(int routeID, int passID);
    void destroyPassAndTickets(int pID);
    void loadAllBase();

    bool changeTicket(int cRouteID, int cPassID, int cStatus);

    void setListPointers(QList<User> *users, QList<Passenger> *passes,
                         QList<Route> *routes, QList<Ticket> *tickets);

    void setPassData(int userID, Passenger &pass);
private:

    static void createHintFile();

    QList<User> *pUserList;
    QList<Passenger> *pPassList;
    QList<Route> *pRoutesList;
    QList<Ticket> *pTicketsList;
};

#endif // DATABASES_H
