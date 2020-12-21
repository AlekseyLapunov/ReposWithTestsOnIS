#ifndef TICKETREQUESTWINDOW_H
#define TICKETREQUESTWINDOW_H

#include <QDialog>
#include <DataBases.h>

namespace Ui {
class TicketRequestWindow;
}

class TicketRequestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TicketRequestWindow(QWidget *parent = nullptr);
    ~TicketRequestWindow();

    void giveDBManagePtr(DataBases *DBPtr);
    void giveUserPtr(User *userPtr);

private slots:
    void doRequest();

private:
    enum {push, change};
    enum {ret, req, del};
    void ticketToBuy(int);
    void ticketToReturn();
    void ticketToDelete();

    void warnBoxSeats();
    void warnBox();
    void gracBox(int);

    DataBases *DBManagePtr;

    User *curUserPtr;
    Ticket ticket;
    Route route;

    Ui::TicketRequestWindow *ui;
};

#endif // TICKETREQUESTWINDOW_H
