#ifndef SQLPARSER_H
#define SQLPARSER_H

#include <QtSql>
#include "satisitem.h"


class sqlParser
{
    QSqlDatabase dataBase;
public:
    sqlParser();

    void dbInitialazer();

    void addItem(QString name, QImage img, QString recipelist);

    void addMachine(QString name, QImage img, QString build_cost, int volume, int power_consumption);

    void addRecipe(QString name, float poduction_time, int quantity, QString ingredients, QString machine_name);

    void createTables();

    void parseFromContentPack(ContentPackage *contentPack);

    void parseFromFile(QFile *file);

};

#endif // SQLPARSER_H
