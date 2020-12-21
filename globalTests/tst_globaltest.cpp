#include <QtTest>
// add necessary includes here
#include <../IS_Airport/Passenger.cpp>
#include <../IS_Airport/Ticket.cpp>

class globalTest : public QObject
{
    Q_OBJECT

public:
    globalTest();
    ~globalTest();

private slots:
    // Проверка метода "починки" ФИО, которая выставляет правильный регистр для букв
    void testFixFullName();
    // Проверка методов определения типа пользователя
    void testTypeDefine();
    // Проверка возвращаемого статуса билета
    void testTicketStatus();
};

globalTest::globalTest()
{

}

globalTest::~globalTest()
{

}

void globalTest::testFixFullName()
{
    QCOMPARE(Passenger::fixFullName("тЕстОВ тест ТЕСТОВИЧ"), "Тестов Тест Тестович");
    QCOMPARE(Passenger::fixFullName("александрова жанна аркадьевна"), "Александрова Жанна Аркадьевна");
    QCOMPARE(Passenger::fixFullName("сТЕПАНОВ сТЕПАН сТЕПАНОВИЧ"), "Степанов Степан Степанович");
    QCOMPARE(Passenger::fixFullName("АЛЕКСЕЕВ АЛЕКСЕЙ АЛЕКСЕЕВИЧ"), "Алексеев Алексей Алексеевич");
    QCOMPARE(Passenger::fixFullName("тЕсТоВ тЕсТ ТеСтОвИч"), "Тестов Тест Тестович");
}

void globalTest::testTypeDefine()
{
    User pass("temp1", "1111", 1, User::idPassenger);
    User cash("temp2", "2222", 2, User::idCashier);
    User admin("temp3", "3333", 3, User::idAdministrator);
    QCOMPARE(pass.getTypeString(), "Passenger");
    QCOMPARE(cash.getTypeString(), "Cashier");
    QCOMPARE(admin.getTypeString(), "Administrator");
    QCOMPARE(pass.getTypeStringRus(), "Пассажир");
    QCOMPARE(cash.getTypeStringRus(), "Кассир");
    QCOMPARE(admin.getTypeStringRus(), "Администратор");
}

void globalTest::testTicketStatus()
{
    Ticket temp(1, 1, Ticket::stReq);
    Ticket temp_2(2, 2, Ticket::stReqAns);
    Ticket temp_3(2, 2, Ticket::stRet);
    Ticket temp_4(3, 3, Ticket::stRetAns);
    QCOMPARE(temp.getStatusStr(), "Покупка");
    QCOMPARE(temp_2.getStatusStr(), "Куплен");
    QCOMPARE(temp_3.getStatusStr(), "Возврат");
    QCOMPARE(temp_4.getStatusStr(), "Возвращён");
    // Дополнительный пятый случай
    Ticket temp_5(1, 4, Ticket::stReqAns);
    QCOMPARE(temp_5.getStatusStr(), "Куплен");
}

QTEST_APPLESS_MAIN(globalTest)

#include "tst_globaltest.moc"
