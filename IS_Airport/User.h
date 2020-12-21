#ifndef USER_H
#define USER_H

#include <string>
#include <QString>
using namespace std;

class User
{
protected:
    // Поле логина
    string login;
    // Поле пароля
    string password;
    // Поле уникального идентификатора
    int ID;
    // Поле типа: не изв., пассажир, кассир, администратор
    int type;

public:
    // Перечисление ID
    enum {idUndefined, idPassenger, idCashier, idAdministrator};

    // Функция возвращает ID
    int getID();
    // Функция возвращает тип пользователя (в формате int)
    int getType();
    // Функция возвращает тип пользователя (в формате QString)
    QString getTypeString();
    // Функция возвращает тип пользователя (в формате QString)
    QString getTypeStringRus();
    // Функция возвращает логин
    string getLogin();
    // Функция возвращает пароль
    string getPassword();

    // Функция изменяет данные пользователя на передаваемые password и type
    void changeAuthInfo(string password, int type);

    User();
    User(string sLogin, string sPassword, int sID, int sType = idPassenger);
};

#endif // USER_H
