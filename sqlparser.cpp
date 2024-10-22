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

void addItem(QString name, QImage img, QString recipelist)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO items ("
                "name TEXT PRIMARY KEY,"
                "icon BLOB,"
                "recipe_list TEXT),"
                "VALUES (?,?,?);");
    qry.addBindValue(name);
    qry.addBindValue(img);
    qry.addBindValue(recipelist);

    if(!qry.exec()) {
        qDebug() << qry.lastError();
    }
}

void addMachine(QString name, QImage img, QString build_cost, int volume, int power_consumption)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO machines ("
                "name TEXT PRIMARY KEY,"
                "icon BLOB,"
                "build_cost TEXT,"
                "volume INTEGER,"
                "power_consumption INTEGER),"
                "VALUES (?,?,?,?,?);");
    qry.addBindValue(name);
    qry.addBindValue(img);
    qry.addBindValue(build_cost);
    qry.addBindValue(volume);
    qry.addBindValue(power_consumption);

    if(!qry.exec()) {
        qDebug() << qry.lastError();
    }
}

void addRecipe(QString name, float poduction_time, int quantity, QString ingredients, QString machine_name)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO recipes ("
                "name TEXT PRIMARY KEY,"
                "poduction_time REAL,"
                "quantity INTEGER,"
                "ingredients TEXT,"
                "machine_name TEXT,"
                "FOREIGN KEY(machine_name) REFERENCES machines(name)),"
                "VALUES (?,?,?,?,?);");
    qry.addBindValue(name);
    qry.addBindValue(poduction_time);
    qry.addBindValue(quantity);
    qry.addBindValue(ingredients);
    qry.addBindValue(machine_name);

    if(!qry.exec()) {
        qDebug() << qry.lastError();
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
void parseFromContentPack(ContentPackage *contentPack)
{
    // adding Machines
    for (int machine_i = 0; machine_i < contentPack->machines.count(); machine_i++)
    {
        // we don't have 3 datas in existing ContentPack.txt yet
        addMachine(
            contentPack->machines[machine_i]->name,
            contentPack->machines[machine_i]->img,
            0,
            0,
            0
            );
    }
    // adding Items (not yet)
    for (int item_i = 0; item_i < contentPack->machines.count(); item_i++)
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
        addItem(
            itemRef->name,
            itemRef->img,
            recipes
        );
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
void parseFromFile(QFile *file)
{
    int debugRecipes = 0;
    ContentPackage content;

    file->readLine();                  // SourceName
    content.name = file->readLine();   // ModuleName
    content.name.removeLast();
    file->readLine();  // Description
    QString img = "";
    QString fileOutput = file->readLine(); fileOutput.removeLast();
    while (fileOutput != "%$")          // Adding machines
    {
        img = file->readLine();
        img.removeLast();
        content.machines.append(new Machine(fileOutput, QImage(QString(":/source/modules/vanilla/machines/%1").arg(img))));
        fileOutput = file->readLine(); fileOutput.removeLast();
    }
    fileOutput = file->readLine(); fileOutput.removeLast();
    QList<QString> UndefinedItems;
    QList<Ingredient*> UndefinedIngredient;
    while (fileOutput != "%$")          // Adding items
    {
        img = file->readLine();
        img.removeLast();
        content.items.append(new Item(fileOutput, QImage(QString(":/source/modules/vanilla/icons/%1").arg(img))));
        Item* lastItem = content.items.last();
        fileOutput = file->readLine(); fileOutput.removeLast();
        qDebug() << "New item: " + lastItem->name;
        for (int i = 0; i<UndefinedItems.count();i++)
        {
            if (lastItem->name == UndefinedItems[i])
            {
                UndefinedIngredient[i]->reference = lastItem;
                UndefinedIngredient.removeAt(i);
                UndefinedItems.removeAt(i);
            }
        }
        while (fileOutput != "%$")      // Adding recipes
        {
            lastItem->recipes.append(new Recipe());
            qDebug() << "Amount of recipes:     " << ++debugRecipes;        // amount of recipes
            Recipe* lastRecipe = lastItem->recipes.last();
            lastRecipe->name = fileOutput;
            fileOutput = file->readLine(); fileOutput.removeLast();
            lastRecipe->machine = content.findMachine(fileOutput);
            fileOutput = file->readLine(); fileOutput.removeLast();
            lastRecipe->quantity = fileOutput.toFloat();
            fileOutput = file->readLine(); fileOutput.removeLast();
            lastRecipe->time = fileOutput.toDouble();
            fileOutput = file->readLine(); fileOutput.removeLast();
            lastRecipe->resCost = fileOutput.toDouble();
            fileOutput = file->readLine(); fileOutput.removeLast();
            while (fileOutput != "%$")  // Adding excess
            {
                lastRecipe->excess.append(new Ingredient());
                Ingredient* lastExcess = lastRecipe->excess.last();
                lastExcess->reference = content.findItem(fileOutput);
                fileOutput = file->readLine(); fileOutput.removeLast();
                lastExcess->quantity = fileOutput.toFloat();
                fileOutput = file->readLine(); fileOutput.removeLast();

                lastExcess->reference->recipes.append(new Recipe());
                Recipe* lastExcessRecipe = lastExcess->reference->recipes.last();
                lastExcessRecipe->name = lastRecipe->name;
                lastExcessRecipe->machine = lastRecipe->machine;
                lastExcessRecipe->quantity = lastExcess->quantity;
                lastExcessRecipe->time = lastRecipe->time;
                lastExcessRecipe->resCost = lastRecipe->resCost;

                lastExcessRecipe->excess.append(new Ingredient());
                lastExcessRecipe->excess.last()->reference = lastItem;
                lastExcessRecipe->excess.last()->quantity = lastRecipe->quantity;

                qDebug() << "New excess: " + lastItem->recipes.last()->excess.last()->reference->name;
            }
            fileOutput = file->readLine(); fileOutput.removeLast();
            qDebug() << "New recipe: " + lastItem->recipes.last()->name;
            Item* ingr = nullptr;
            while (fileOutput != "%$")  // Adding ingredients
            {
                lastItem->recipes.last()->ingredients.append(new Ingredient());
                Ingredient* lastIngredient = lastItem->recipes.last()->ingredients.last();
                ingr = content.findItem(fileOutput);
                if (ingr)
                {
                    lastIngredient->reference = ingr;
                }
                else
                {
                    qDebug() << "Item (" << fileOutput << ") didn't find!";
                    UndefinedItems.append(fileOutput);
                    qDebug() << "Item (" << fileOutput << ") appended into the list";
                    UndefinedIngredient.append(lastIngredient);
                    qDebug() << "Ingredient (" << fileOutput << ") appended into the list";
                }
                fileOutput = file->readLine(); fileOutput.removeLast();
                lastIngredient->quantity = fileOutput.toFloat();
                fileOutput = file->readLine(); fileOutput.removeLast();
                if (lastIngredient->reference)
                    qDebug() << "New Ingredient: " + lastIngredient->reference->name;
                else
                    qDebug() << "New Ingredient: " + UndefinedItems.last() + " / ! \\ UNDEFINED YET / ! \\";

                if (lastItem->recipes.last()->excess.count())
                {
                    lastItem->recipes.last()->excess.last()->reference->recipes.last()->ingredients.append(new Ingredient());
                    lastItem->recipes.last()->excess.last()->reference->recipes.last()->ingredients.last()->reference = lastIngredient->reference;
                    lastItem->recipes.last()->excess.last()->reference->recipes.last()->ingredients.last()->quantity = lastIngredient->quantity;
                    qDebug() << "New excess Ingredient: " + lastIngredient->reference->name;
                }
            }
            fileOutput = file->readLine(); fileOutput.removeLast();
        }
        fileOutput = file->readLine(); fileOutput.removeLast();
    }
    parseFromContentPack(&content);
}
