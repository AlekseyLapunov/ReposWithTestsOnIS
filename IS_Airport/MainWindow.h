#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <AuthWindow.h>
#include <QMainWindow>
#include <User.h>
#include <DataBases.h>
#include <QMessageBox>
#include <UsersViewWindow.h>
#include <PassesViewWindow.h>
#include <RoutesViewWindow.h>
#include <ManageRoutesWindow.h>
#include <TicketRequestWindow.h>
#include <TicketsViewWindow.h>
#include <MyInfoWindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool MainWindowClosed = true;
    bool authWindowClosed = false;

    void setNulls();

private slots:

    void viewUsers();
    void viewPasses();
    void viewMyInfo();
    void manageRoutes();
    void viewRoutes();
    void viewTickets();
    void doRequest();
    void quit();
    void tellAbout();

private:
    // Текущий пользователь
    User currentUser;
    // Текущий пассажир
    Passenger currentPass;

    // Список пользователей
    QList<User> UsersList;
    // Список пассажиров
    QList<Passenger> PassesList;
    // Список билетов
    QList<Ticket> TicketsList;
    // Список рейсов
    QList<Route> RoutesList;

    void manageWidgets();
    void giveAllPtrs();

    // Объект взаимодействия с базами данных
    DataBases DBManager;

    // Окно авторизации
    AuthWindow authWindow;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
