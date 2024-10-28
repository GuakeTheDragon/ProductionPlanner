#include "sqlparser.h"

sqlParser::sqlParser()
{
    dbInitialazer(dataBaseName);

}

int sqlParser::dbInitialazer(QString DBName)
{
    if (dataBase.isOpen()) {
        dataBase.close();
        dataBase.removeDatabase( QSqlDatabase::defaultConnection );
    }

    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName(DBName);

    if(!dataBase.open()) {
        qDebug() << "dataBase opening problem\n";
        return 1;
    }
    return 0;
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
    QString query = "CREATE TABLE IF NOT EXISTS items ("
                    "name TEXT PRIMARY KEY,"
                    "icon BLOB,"
                    "recipe_list TEXT);";
    QSqlQuery qry;

    if(!qry.exec(query)) {
        qDebug() << "error creating table\n" << qry.lastError();
    }

    query = "CREATE TABLE IF NOT EXISTS machines ("
            "name TEXT PRIMARY KEY,"
            "icon BLOB,"
            "build_cost TEXT,"
            "volume INTEGER,"
            "power_consumption INTEGER);";

    if(!qry.exec(query)) {
        qDebug() << "error creating table\n" << qry.lastError();
    }

    query = "CREATE TABLE IF NOT EXISTS recipes ("
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
    // byte array for icon storage
    // buffer for byte array writing
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

int sqlParser::fillContentPack(ContentPackage *contentPack, int fillMode, QString DBName)
{
    QImage icon;

    // setting content pack filling mode
    switch (fillMode) {
    case CPExtend:
        break;
    case CPNew:
        contentPack->items.clear();
        contentPack->machines.clear();
    default:
        qDebug() << "fillContentPack: Chosen fill mode does not exit!\n";
        return 1;
    }
    // changing data base if needed
    if (DBName != dataBaseName) {
        if (dbInitialazer(DBName)) {
            qDebug() << "fillContentPack: Failed initializing new data base\n";
            return 2;
        }
    }
    //filling recipes and machines
    QSqlQuery qry;
    qry.prepare("SELECT * FROM recipes JOIN machines ON machines.name = recipes.machine_name");

    if(!qry.exec()) {
        qDebug() << "fillContentPack: " << qry.lastError();
        return 3;
    }


    while (qry.next()) {
        QString    recipe_name               = qry.value(0).toString();
        double     recipe_production_time    = qry.value(1).toDouble();
        int        recipe_quantity           = qry.value(2).toInt();
        QString    recipe_ingredients        = qry.value(3).toString();
        QString    machine_name              = qry.value(5).toString();
        QByteArray machine_icon_byteArr      = qry.value(6).toByteArray();
        QString    machine_buid_cost         = qry.value(7).toString();
        int        machine_volume            = qry.value(8).toInt();
        int        machine_power_consunption = qry.value(9).toInt();

        // converting QByteArray to QImage
        if(!icon.loadFromData(machine_icon_byteArr, "PNG"))
            qDebug()<<"Image was not loaded";

        // .....
    }

    //filling items
    qry.prepare("SELECT * FROM items");

    if(!qry.exec()) {
        qDebug() << "fillContentPack: " << qry.lastError();
        return 3;
    }


    while (qry.next()) {
        QString    item_name         = qry.value(0).toString();
        QByteArray item_icon_byteArr = qry.value(1).toByteArray();
        QString    item_recipe_list  = qry.value(2).toString();

        // converting QByteArray to QImage
        if(!icon.loadFromData(item_icon_byteArr, "PNG"))
            qDebug()<<"Image was not loaded";

        // .....
    }
}





















