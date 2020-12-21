#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QApplication"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setNulls();
    MainWindow::giveAllPtrs();
    DBManager.loadAllBase();

    // Вызов окна авторизации
    authWindow.exec();
   if(!authWindowClosed)
   {
       MainWindowClosed = false;
       MainWindow::manageWidgets();
       this->show();
       if(currentUser.getType() == User::idPassenger)
       DBManager.setPassData(currentUser.getID(), currentPass);
   }
}

MainWindow::~MainWindow()
{
    MainWindow::setNulls();
    delete ui;
}

void MainWindow::giveAllPtrs()
{
    DBManager.setListPointers(&UsersList, &PassesList,
                              &RoutesList, &TicketsList);
    authWindow.giveDBManagerPtr(&DBManager);
    authWindow.giveFlag(authWindowClosed);
    authWindow.giveUserPtr(currentUser);
    authWindow.givePassPtr(currentPass);
}

void MainWindow::setNulls()
{
    UsersList.clear();
    PassesList.clear();
    TicketsList.clear();
    RoutesList.clear();
}

void MainWindow::viewUsers()
{
    if(this->currentUser.getType() == User::idAdministrator)
    {
        // Окно просмотра пользователей
        UsersViewWindow usersWindow;
        usersWindow.giveDBManagerPtr(&DBManager);
        usersWindow.giveListPtr(&UsersList);
        usersWindow.giveCurUserPtr(&currentUser);
        usersWindow.fillTable();
        usersWindow.exec();
    }
}

void MainWindow::viewPasses()
{
    if(this->currentUser.getType() == User::idAdministrator)
    {
        // Окно просмотра пассажиров
        PassesViewWindow passesWindow;
        passesWindow.giveDBManagerPtr(&DBManager);
        passesWindow.giveListPtr(&PassesList);
        passesWindow.fillTable();
        passesWindow.exec();
    }
}

void MainWindow::viewMyInfo()
{
    if(this->currentUser.getType() == User::idPassenger)
    {
        // Окно просмотра пассажиров
        MyInfoWindow myInfoWindow;
        myInfoWindow.giveTicketsListPtr(&TicketsList);
        myInfoWindow.givePassPtr(&currentPass);
        myInfoWindow.fillTable();
        myInfoWindow.exec();
    }
}

void MainWindow::viewRoutes()
{
    // Окно просмотра рейсов
    RoutesViewWindow routesWindow;
    routesWindow.giveDBManagerPtr(&DBManager);
    routesWindow.giveListPtr(&RoutesList);
    routesWindow.fillTable();
    routesWindow.exec();
}

void MainWindow::viewTickets()
{
    if(currentUser.getType() == User::idAdministrator
       || currentUser.getType() == User::idCashier)
    {
        // Окно просмотра рейсов
        TicketsViewWindow ticketsWindow;
        ticketsWindow.giveDBManagerPtr(&DBManager);
        ticketsWindow.giveListPtr(&TicketsList);
        ticketsWindow.fillTable();
        ticketsWindow.exec();
    }
}

void MainWindow::doRequest()
{
    TicketRequestWindow tReqWindow;
    tReqWindow.giveDBManagePtr(&DBManager);
    tReqWindow.giveUserPtr(&currentUser);
    tReqWindow.exec();
}

void MainWindow::quit()
{
    QMessageBox quitBox(this);
    quitBox.setIcon(QMessageBox::Question);
    quitBox.setWindowTitle("Выход");
    quitBox.setText(tr("Вы уверены, что хотите<br> выйти из программы?"));
    quitBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    quitBox.setDefaultButton(QMessageBox::Yes);
    if(quitBox.exec() == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

void MainWindow::tellAbout()
{
    QMessageBox aboutDlg(this);
    aboutDlg.setTextFormat(Qt::RichText);
    aboutDlg.setWindowTitle(tr("О ИС Аэропорт"));
    aboutDlg.setIcon(QMessageBox::Information);
    aboutDlg.setText(tr("<br>"
            "Информационная система \"Аэропорт\" является учебной программой,<br> разработанной"
            " студентом группы КИ19-08б (направление 09.03.01) с целью выполнения поставленной"
            " задачи в рамках учебного процесса.<br>""Автор (студент): Лапунов Алексей Юрьевич.<br>"
                        "Преподаватель: Васильев Владимир Сергеевич."));
    aboutDlg.exec();
}

void MainWindow::manageRoutes()
{
    if(this->currentUser.getType() == User::idAdministrator
            || this->currentUser.getType() == User::idCashier)
    {
        // Окно Создания/Удаления рейсов
        ManageRoutesWindow *manageRoutesWindow = new ManageRoutesWindow();
        manageRoutesWindow->giveDBPtr(&DBManager);
        manageRoutesWindow->show();
    }
}

void MainWindow::manageWidgets()
{
    setWindowTitle(tr("ИС Аэропорт"));
    if(this->currentUser.getType() == User::idAdministrator)
    {
        ui->myInfoButton->setHidden(true);
        ui->makeRequestButton->setHidden(true);
    }
    else if (this->currentUser.getType() == User::idCashier)
    {
        ui->myInfoButton->setHidden(true);
        ui->makeRequestButton->setHidden(true);
        ui->viewUsersButton->setHidden(true);
        ui->viewPassesButton->setHidden(true);
    }
    else if (this->currentUser.getType() == User::idPassenger)
    {
        ui->label->setText(tr("Добро пожаловать, %1").arg(this->currentPass.getFullName()));
        ui->viewUsersButton->setHidden(true);
        ui->viewPassesButton->setHidden(true);
        ui->manageRoutesButton->setHidden(true);
        ui->viewRequestsButton->setHidden(true);
    }
}










