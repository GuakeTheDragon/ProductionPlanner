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

void sqlParser::addItem(QString name, QByteArray img)
{
    QSqlQuery qry;

    qry.prepare("INSERT OR REPLACE INTO items ("
                "name,"
                "icon)"
                "VALUES (:name, :icon);");
    qry.bindValue(":name", name);
    qry.bindValue(":icon", img);

    if(!qry.exec()) {
        qDebug() << "addItem: " << qry.lastError();
    }
}

void sqlParser::addMachine(QString name, QByteArray img, QString build_cost, int volume, int power_consumption)
{
    QSqlQuery qry;

    qry.prepare("INSERT OR REPLACE INTO machines ("
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

void sqlParser::addRecipe(QString name, float poduction_time, int quantity, QString ingredients, double recipe_cost, QString machine_name, QString item_name)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO recipes ("
                "name,"
                "poduction_time,"
                "quantity,"
                "ingredients,"
                "recipe_cost,"
                "machine_name,"
                "item_name)"
                "VALUES (:name, :production_time, :quantity, :ingredients, :recipe_cost, :machine_name, :item_name);");
    qry.bindValue(":name", name);
    qry.bindValue(":production_time", poduction_time);
    qry.bindValue(":quantity", quantity);
    qry.bindValue(":ingredients" ,ingredients);
    qry.bindValue(":recipe_cost", recipe_cost);
    qry.bindValue(":machine_name", machine_name);
    qry.bindValue(":item_name", item_name);

    if(!qry.exec()) {
        qDebug() << "addRecipe: " << qry.lastError();
    }
}

void sqlParser::createTables()
{
    QString query = "CREATE TABLE IF NOT EXISTS items ("
                    "name TEXT PRIMARY KEY,"
                    "icon BLOB);";
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
            "recipe_cost REAL,"
            "machine_name TEXT,"
            "item_name TEXT,"
            "FOREIGN KEY(machine_name) REFERENCES machines(name),"
            "FOREIGN KEY(item_name) REFERENCES items(name));";

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
        Item* itemRef = contentPack->items[item_i];         // for readability                              // for adding recipe list into SQLite
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
                recipeRef->resCost,
                recipeRef->machine->name,
                itemRef->name
            );
        }
        // adding items NOW
        itemRef->img.save(&buffer, "PNG");
        addItem(
            itemRef->name,
            byteArray
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

bool sqlParser::fillItems(ContentPackage *contentPack)
{
    QImage icon;
    QSqlQuery qry;

    qry.prepare("SELECT * FROM items");

    if(!qry.exec()) {
        qDebug() << "fillCoptentPack: fillItems. " << qry.lastError();
        return true;
    }
    while (qry.next()) {
        QString    item_name                 = qry.value(0).toString();
        QByteArray item_icon_byteArr         = qry.value(1).toByteArray();

        if(!icon.loadFromData(item_icon_byteArr, "PNG"))                  // converting QByteArray Item icon to QImage
            qDebug()<<"Image was not loaded";
        Item *item = new Item(item_name, icon);
        contentPack->items.push_back(item);
    }

    return false;
}

bool sqlParser::fillMachines(ContentPackage *contentPack)
{
    QImage icon;
    QSqlQuery qry;

    qry.prepare("SELECT * FROM machines");

    if(!qry.exec()) {
        qDebug() << "fillCoptentPack: fillMachines. " << qry.lastError();
        return true;
    }
    while (qry.next()) {
        QString    machine_name              = qry.value(0).toString();
        QByteArray machine_icon_byteArr      = qry.value(1).toByteArray();
        QString    machine_buid_cost         = qry.value(2).toString();    //should
        int        machine_volume            = qry.value(3).toInt();       //  add more
        int        machine_power_consunption = qry.value(4).toInt();       //     constructors

        if(!icon.loadFromData(machine_icon_byteArr, "PNG"))                  // converting QByteArray Machine icon to QImage
            qDebug()<<"Image was not loaded";
        Machine *machine = new Machine(machine_name, icon, machine_power_consunption);
        contentPack->machines.push_back(machine);
    }

    return false;
}

bool sqlParser::fillRecipes(ContentPackage *contentPack)
{
    QSqlQuery qry;

    qry.prepare("SELECT * FROM recipes");

    if(!qry.exec()) {
        qDebug() << "fillContentPack: fillRecipes. " << qry.lastError();
        return true;
    }
    while (qry.next()) {
        QString    recipe_name               = qry.value(0).toString();
        double     recipe_production_time    = qry.value(1).toDouble();
        int        recipe_quantity           = qry.value(2).toInt();
        QString    recipe_ingredients        = qry.value(3).toString();
        double     recipe_cost               = qry.value(4).toDouble();
        QString    machine_name              = qry.value(5).toString();
        QString    item_name                 = qry.value(6).toByteArray();

        Machine* machineRef = contentPack->findMachine(machine_name);
        // several of machine values are in recipe class for some reason?????????
        Recipe *recipe = new Recipe(
            recipe_name,
            machineRef,
            recipe_quantity,
            recipe_production_time,
            machineRef->powerConsunption,
            recipe_cost
        );

        QString temp = "";
        while(recipe_ingredients != "") {
            temp = recipe_ingredients.split('\t').at(0);
            recipe_ingredients.erase(recipe_ingredients.begin(), recipe_ingredients.begin() + temp.size() + 1);
            Ingredient *ingredient = new Ingredient (contentPack->findItem(temp), 0);
            temp = recipe_ingredients.split('\t').at(0);
            recipe_ingredients.erase(recipe_ingredients.begin(), recipe_ingredients.begin() + temp.size() + 1);
            ingredient->quantity = temp.toInt();
            recipe->ingredients.push_back(ingredient);
        }

        contentPack->findItem(item_name)->recipes.push_back(recipe);
    }

    return false;
}

int sqlParser::fillContentPack(ContentPackage *contentPack, int fillMode, QString DBName)
{
                                                            // setting content pack filling mode
    switch (fillMode) {
    case CPExtend:
        break;
    case CPNew:
        contentPack->items.clear();
        contentPack->machines.clear();
        break;
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
                                                            // filling content package

    if (fillItems(contentPack))
    {
        qDebug() << "fillCoptentPack: fillItems error.";
        return 3;
    }
    if (fillMachines(contentPack))
    {
        qDebug() << "fillCoptentPack: fillMachines error.";
        return 4;
    }
    if (fillRecipes(contentPack))
    {
        qDebug() << "fillCoptentPack: fillRecipes error.";
        return 5;
    }

    return 0;
}





















