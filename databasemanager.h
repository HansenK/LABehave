#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

using namespace std;

class DatabaseManager
{
public:
    DatabaseManager();

    int getTestId() { return testId; }
    void newTest(QString name);

private:
    QSqlDatabase db;
    int testId;
};

#endif // DATABASEMANAGER_H
