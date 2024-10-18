#ifndef SQLPARSER_H
#define SQLPARSER_H

#include <QtSql>

class sqlParser
{
    QSqlDatabase dataBase;
public:
    sqlParser();

    void dbInitialazer();

    void createTables();




};

#endif // SQLPARSER_H
