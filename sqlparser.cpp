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

void sqlParser::addItem(QString name, QByteArray img, QString recipe_list)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO items ("
                "name,"
                "icon,"
                "recipe_list)"
                "VALUES (:name, :icon, :recipe_list);");
    qry.bindValue(":name", name);
    qry.bindValue(":icon", img);
    qry.bindValue(":recipelist", recipe_list);

    if(!qry.exec()) {
        qDebug() << "addItem: " << qry.lastError();
    }
}

void sqlParser::addMachine(QString name, QByteArray img, QString build_cost, int volume, int power_consumption)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO machines ("
                "name,"
                "icon,"
                "build_cost,"
                "volume,"
                "power_consumption)"
                "VALUES (:name, :icon, :build_cost, :volume, :power_consumption);");
    qry.bindValue(":name", name);
    qry.bindValue(":icon", img);
    qry.bindValue(":build_cost", build_cost);
    qry.bindValue(":volume", volume);
    qry.bindValue(":power_consumption", power_consumption);

    if(!qry.exec()) {
        qDebug() << "addMachine: " << qry.lastError();
    }
}

void sqlParser::addRecipe(QString name, float poduction_time, int quantity, QString ingredients, QString machine_name)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO recipes ("
                "name,"
                "poduction_time,"
                "quantity,"
                "ingredients,"
                "machine_name)"
                "VALUES (:name, :production_time, :quantity, :ingredients, :machine_name);");
    qry.bindValue(":name", name);
    qry.bindValue(":production_time", poduction_time);
    qry.bindValue(":quantity", quantity);
    qry.bindValue(":ingredients" ,ingredients);
    qry.bindValue(":machine_name", machine_name);

    if(!qry.exec()) {
        qDebug() << "addRecipe: " << qry.lastError();
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

// a complex structure of HOW do items/ingredients refer to each other
// it seems way too complicate to add a more suitable parsing function
// from a .txt file
// than just parse from a complete Content Package
void sqlParser::parseFromContentPack(ContentPackage *contentPack)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    // adding Machines
    for (int machine_i = 0; machine_i < contentPack->machines.count(); machine_i++)
    {
        // we don't have 3 datas in existing ContentPack.txt yet

        contentPack->machines[machine_i]->img.save(&buffer, "PNG");
        addMachine(
            contentPack->machines[machine_i]->name,
            byteArray,
            "0",
            0,
            0
            );
        buffer.reset();
        byteArray.clear();
    }
    // adding Items (not yet)
    for (int item_i = 0; item_i < contentPack->items.count(); item_i++)
    {
        Item* itemRef = contentPack->items[item_i];         // for readability
        QString recipes = "";                               // for adding recipe list into SQLite
        // adding recipes (not yet)
        // due to how we read content of a ContentPackage
        for (int recipe_i = 0; recipe_i < itemRef->recipes.count(); recipe_i++)
        {
            Recipe* recipeRef = itemRef->recipes[recipe_i]; // for readability
            QString ingredients = "";                       // for adding ingredient list into SQLite
            for (int ingredient_i = 0; ingredient_i < recipeRef->ingredients.count(); ingredient_i++)
            {
                ingredients += recipeRef->ingredients[ingredient_i]->reference->name;
                ingredients += "\t";    // probably not the best diversion symbol
                ingredients += QString::number(recipeRef->ingredients[ingredient_i]->quantity);
                ingredients += "\t";    // put another diversion symbol if there are better ones
            }
            // adding recipes NOW
            addRecipe(
                recipeRef->name,
                recipeRef->time,
                recipeRef->quantity,
                ingredients,
                recipeRef->machine->name
            );
            recipes += recipeRef->name;
            recipes += "\t";
        }
        // adding items NOW
        itemRef->img.save(&buffer, "PNG");
        addItem(
            itemRef->name,
            byteArray,
            recipes
        );
        buffer.reset();
        byteArray.clear();
    }
}

// Obsolete code
// Technically can be used
// Practically won't be used (consider use parseFromContentPack() then)
// ..simply because it's just creating temporary ContentPackage class, fill it and parse the class instead
// HOWEVER not recomended to delete in case the programm REALLY will MUST to parse from FILES
// (as stated above, parse from file is way harder (if not impossible) in case of how do SQLite work)

// also consider Windows somewhy add /r/n in the end of .txt
// meanwhile there are only /n on Linux
// so probably it's a good idea to make a deletion of /r and /n by a search and not from removeLast()
void sqlParser::parseFromFile(QFile *file)
{
    ContentPackage content;
    content.refill(file);
    parseFromContentPack(&content);
}
