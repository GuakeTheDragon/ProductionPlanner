#include "sqlparser.h"

sqlParser::sqlParser()
{
    dbInitialazer();
}

void sqlParser::dbInitialazer()
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("myDb.sqlite");

    if(!dataBase.open()) {
        qDebug() << "dataBase opening problem\n";
    }
}

void sqlParser::createTables()
{
    QString query = "CREATE TABLE items ("
                    "name TEXT PRIMARY KEY,"
                    "icon BLOB,"
                    "recipe_list TEXT);";
    QSqlQuery qry;

    if(!qry.exec(query)) {
        qDebug() << "error creating table\n" << qry.lastError();
    }

    query = "CREATE TABLE machines ("
            "name TEXT PRIMARY KEY,"
            "icon BLOB,"
            "build_cost TEXT,"
            "volume INTEGER,"
            "power_consumption INTEGER);";

    if(!qry.exec(query)) {
        qDebug() << "error creating table\n" << qry.lastError();
    }

    query = "CREATE TABLE recipes ("
            "name TEXT PRIMARY KEY,"
            "poduction_time REAL,"
            "quantity INTEGER,"
            "ingredients TEXT,"
            "machine_name TEXT,"
            "FOREIGN KEY(machine_name) REFERENCES machines(name));";

    if(!qry.exec(query)) {
        qDebug() << "error creating table\n" << qry.lastError();
    }
}
