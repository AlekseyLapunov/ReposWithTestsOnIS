#ifndef USERSBASE_H
#define USERSBASE_H

#include <User.h>
#include <string>
#include <QString>
#include <QList>

class UsersBase
{
public:
    UsersBase();

    // Создаёт запись в двоичном файле потока qstream
    static void createUserNote(QString login, QString password, int ID, int type, QDataStream &qstream);

    // Функция находит пользователя в базе данных
    static bool find(string login, string password, User &fUser);

    // Функция находит пользователя в базе данных
    static bool find(int id, string login, User &fUser);
    // Функция находит пользователя в базе данных
    static bool find(string login, User &fUser);

    // Функция находит логин в базе данных
    static bool find(string login);

    static void refreshBase(QList<User> &pUserList);

    static void loadBase(QList<User> &pUserList);

private:

};

#endif // USERSBASE_H
