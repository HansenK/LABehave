#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("labehave");
    db.setUserName("root");
    db.setPassword("Cthulhu.Waits.Dreaming");
    if(db.open()) {
        QSqlQuery query;
        // cria as tabelas caso nao existam

        // testes
        query.exec("CREATE TABLE IF NOT EXISTS tests( id int not null auto_increment PRIMARY KEY, name varchar(20) )");
        // eventos
        query.exec("CREATE TABLE IF NOT EXISTS events( id INT NOT NULL, name VARCHAR(45) NULL, counter INT NULL, id_test INT NULL, PRIMARY KEY (`id`)) ");
        // ocorrencia de eventos
        query.exec("CREATE TABLE IF NOT EXISTS event_occur ( id INT NOT NULL, name VARCHAR(45) NULL, start DOUBLE NULL, end DOUBLE NULL, id_test INT NULL, PRIMARY KEY (`id`))");
        // zonas
        query.exec("CREATE TABLE IF NOT EXISTS zones ( id INT NOT NULL, zone INT NULL, permTime DOUBLE NULL, id_test INT NULL, PRIMARY KEY (`id`))");
        // informacoes sobre a cobaia
        query.exec("CREATE TABLE IF NOT EXISTS animal ( id INT NOT NULL, type VARCHAR(20) NULL, maxVel DOUBLE NULL, id_test INT NULL, PRIMARY KEY (`id`))");

    } else{
        qDebug() << db.lastError().text();
        qApp->quit();
    }
}

void DatabaseManager::newTest(QString name) {
    QSqlQuery query;
    query.prepare("INSERT INTO tests (id, name) VALUES (null, :name)");
    query.bindValue(":name", name);
    query.exec();

    testId = query.lastInsertId().toInt();
    qDebug() << testId;
}
