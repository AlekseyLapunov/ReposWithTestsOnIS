#ifndef ROUTESVIEWWINDOW_H
#define ROUTESVIEWWINDOW_H

#include <QDialog>
#include <DataBases.h>
#include <Route.h>
#include <QStandardItemModel>

namespace Ui {
class RoutesViewWindow;
}

class RoutesViewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RoutesViewWindow(QWidget *parent = nullptr);
    ~RoutesViewWindow();

    void giveDBManagerPtr(DataBases *DBPointer);
    void giveListPtr(QList<Route> *sRouteListPtr);
    void fillTable(bool def = true);

private slots:
    void startFilter();

private:
    DataBases *DBManagerPtr;

    QList<Route> routesToShow;
    QList<Route> *routesListPtr;

    void refreshListPtr();

    QStandardItemModel *table;

    Ui::RoutesViewWindow *ui;
};

#endif // ROUTESVIEWWINDOW_H
