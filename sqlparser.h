#ifndef SQLPARSER_H
#define SQLPARSER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QBuffer>
#include "satisitem.h"


class sqlParser
{
    QSqlDatabase dataBase;

    void dbInitialazer();
public:
    sqlParser();

    void addItem(QString name, QByteArray byteArray, QString recipe_list);

    void addMachine(QString name, QByteArray img, QString build_cost, int volume, int power_consumption);

    void addRecipe(QString name, float poduction_time, int quantity, QString ingredients, QString machine_name);

    void createTables();

    void parseFromContentPack(ContentPackage *contentPack);

    void parseFromFile(QFile *file);

};

#endif // SQLPARSER_H
