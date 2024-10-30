#ifndef SQLPARSER_H
#define SQLPARSER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QBuffer>
#include <QDebug>
#include "satisitem.h"


class sqlParser
{


    QSqlDatabase dataBase;

    QString dataBaseName = "baseContentPack.sqlite";

    int dbInitialazer(QString DBName);
public:
    enum {
        CPExtend = 1,
        CPNew = 2,
    };

    sqlParser();

    void addItem(QString name, QByteArray byteArray);

    void addMachine(QString name, QByteArray img, QString build_cost, int volume, int power_consumption);

    void addRecipe(QString name, float poduction_time, int quantity, QString ingredients, double recipe_cost, QString machine_name, QString item_name);

    void createTables();

    void parseFromContentPack(ContentPackage *contentPack);

    void parseFromFile(QFile *file);

    bool fillItems(ContentPackage *contentPack);

    bool fillMachines(ContentPackage *contentPack);

    bool fillRecipes(ContentPackage *contentPack);

    int fillContentPack(ContentPackage *contentPack, int fillMode = CPExtend, QString DBName = "baseContentPack.sqlite");

};

#endif // SQLPARSER_H
