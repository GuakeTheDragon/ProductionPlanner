#include "satisitem.h"


void AvailableMod::setType(QString str)
{
    type = str;
}
void AvailableMod::setName(QString str)
{
    name = str;
}
void AvailableMod::setDesc(QString str)
{
    description = str;
}

// AVAILABLE MODULES
AvailableModules::AvailableModules(QObject *parent) :
    QAbstractTableModel(parent)
{

}
int AvailableModules::rowCount(const QModelIndex &) const
{
    return list.count();
}
int AvailableModules::columnCount(const QModelIndex &) const
{
    return 3;
}
QVariant AvailableModules::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        if (index.column() == 0)
            return QString(list.at(index.row()).type);
        if (index.column() == 1)
            return QString(list.at(index.row()).name);
        if (index.column() == 2)
            return QString(list.at(index.row()).description);
    case Qt::SizeHintRole:
        return QSize(0,16);
    case Qt::EditRole:
        switch (index.column())
        {
        case 0:
            return list[index.row()].type;
        case 1:
            return list[index.row()].name;
        case 2:
            return list[index.row()].description;
        }
    default:
        return QVariant();
    }
}
QVariant AvailableModules::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Type");
        case 1:
            return QString("Name");
        case 2:
            return QString("Description");
        }
    }
    return QVariant();
}
bool AvailableModules::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        switch (index.column())
        {
        case 0:
            list[index.row()].setType(value.toString());
            break;
        case 1:
            list[index.row()].setName(value.toString());
            break;
        case 2:
            list[index.row()].setDesc(value.toString());
            break;
        }
    }
    emit dataChanged(this->index(0,0), this->index(this->list.size(),2));
    return 0;
}
Qt::ItemFlags AvailableModules::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | /*Qt::ItemIsUserCheckable |*/ Qt::ItemIsEditable | Qt::ItemIsSelectable;
}
void AvailableModules::add(const QModelIndex &index)
{
    beginInsertRows(QModelIndex(), index.row()+1, index.row()+1);
    endInsertRows();
}
void AvailableModules::remove(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    endRemoveRows();
}

//FOR MODULES
void Recipe::setInclusion(int i)
{
    if (i == 2)
        inclusion = Qt::Checked;
    else if (i == 1)
        inclusion = Qt::PartiallyChecked;
    else
        inclusion = Qt::Unchecked;
}
void Item::setInclusion(int i)
{
    if (i == 2)
        inclusion = Qt::Checked;
    else if (i == 1)
        inclusion = Qt::PartiallyChecked;
    else
        inclusion = Qt::Unchecked;
}
void ContentPackage::setInclusion(int i)
{
    if (i == 2)
        inclusion = Qt::Checked;
    else if (i == 1)
        inclusion = Qt::PartiallyChecked;
    else
        inclusion = Qt::Unchecked;
}
bool ContentPackage::refill(QFile *file)
{
    int debugRecipes = 0;

    file->readLine();                // SourceName
    this->name = file->readLine();   // ModuleName
    this->name.removeLast();
    /*while text*/file->readLine();  // Description
        //smthg
    /*while end file->readLine();*/   // WIP
    //smthg
    QString img = "";
    QString fileOutput = file->readLine(); fileOutput.removeLast();
    while (fileOutput != "%$")          // Adding machines
    {
        img = file->readLine();
        img.removeLast();
        this->machines.append(new Machine(fileOutput, QImage(QString(":/source/modules/vanilla/machines/%1").arg(img))));
        fileOutput = file->readLine(); fileOutput.removeLast();
    }
    fileOutput = file->readLine(); fileOutput.removeLast();
    QList<QString> UndefinedItems;
    QList<Ingredient*> UndefinedIngredient;
    while (fileOutput != "%$")          // Adding items
    {
        img = file->readLine();
        img.removeLast();
        this->items.append(new Item(fileOutput, QImage(QString(":/source/modules/vanilla/icons/%1").arg(img))));
        Item* lastItem = this->items.last();
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
            lastRecipe->machine = this->findMachine(fileOutput);
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
                lastExcess->reference = this->findItem(fileOutput);
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
                ingr = this->findItem(fileOutput);
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
    return 0;
}
Machine* ContentPackage::findMachine(QString name)
{
    for(int i=0; i<machines.count(); i++)
    {
        if (machines[i]->name == name)
            return machines[i];
    }
    return nullptr;
}
Item* ContentPackage::findItem(QString name)
{
    for(int i=0; i<items.count(); i++)
    {
        if (items[i]->name == name)
            return items[i];
    }
    return nullptr;
}

void ProductionBranch::transformToQTree(QTreeWidgetItem* branch)
{
    qDebug() << "Making tree for: " + this->item->name;
    branch->setIcon(0, QIcon(QPixmap::fromImage(this->item->img)));
    QString branchText = "";
    branchText += QString::number(this->speed, 'g', 5);
    branchText += "/m ";
    branchText += item->name;
    branch->setText(0, branchText);
    branchText = "";
    qDebug() << "Made tree for: " + this->item->name;

    if (!this->recipe)
        return;

    for (int i=0;i<this->recipe->excess.count();i++)
    {
        Ingredient* jExcess = this->recipe->excess.at(i);
        qDebug() << "Making excess for: " + jExcess->reference->name;
        branch->setIcon(1, QIcon(QPixmap::fromImage(jExcess->reference->img)));
        branchText += QString::number(speed * (double(jExcess->quantity) / double(this->recipe->quantity)), 'g', 5);
        branchText += "/m ";
        branchText += jExcess->reference->name;
        branch->setText(1, branchText);
        branchText = "";
    }

    qDebug() << "Adding machine: " + this->item->name;
    branch->setIcon(2, QIcon(QPixmap::fromImage(this->recipe->machine->img)));
    branchText += this->recipe->machine->name;
    branchText += ": ";
    branchText += this->recipe->name;
    branchText += "; Cost: ";
    branchText += QString::number(this->cost * speed);
    branch->setText(2, branchText);

    qDebug() << "Adding ingredients: " + this->item->name;
    for (int i=0;i<this->recipe->ingredients.count();i++)
    {
        branch->addChild(new QTreeWidgetItem);
        this->children.at(i)->transformToQTree(branch->child(branch->childCount() - 1));
    }

}

// SET MODULES
Modules::Modules(QObject *parent) :
    QAbstractTableModel(parent)
{

}
int Modules::rowCount(const QModelIndex &) const
{
    return items.count();
}
int Modules::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant Modules::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0:
            return items.at(index.row())->name;
        case 1:
            return items.at(index.row())->recipes.at(index.row())->name;
        case 2:
            return items.at(index.row())->recipes.at(index.row())->ingredients.at(index.row())->reference->name;
        }

        return items.at(index.row())->name;
    case Qt::SizeHintRole:
        return QSize(16,16);
    case Qt::DecorationRole:
        return (items.at(index.row())->img).scaled(32,32);
    case Qt::CheckStateRole:
        return items.at(index.row())->inclusion;
    default:
        return QVariant();
    }
}
bool Modules::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch (role)
    {
    case Qt::CheckStateRole:
        items.at(index.row())->setInclusion(value.toInt());
        break;
    default:
        break;
    }
    emit dataChanged(this->index(0,0), this->index(this->items.size(),0));
    return 0;
}
Qt::ItemFlags Modules::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
int Modules::itemsCount()
{
    return items.count();
}
void Modules::addContentPack(ContentPackage* pack)
{
    for (Item* i : pack->items) {
        items.append(i);
    }
    for (Machine* i : pack->machines){
        machines.append(i);
    }
}
void Modules::swapItemInclusion(const QModelIndex &index)
{
    items.at(index.row())->setInclusion(!items.at(index.row())->inclusion * 2);
    for (Recipe* i : items.at(index.row())->recipes)
    {
        i->setInclusion(items.at(index.row())->inclusion);
    }
}
Item* Modules::getItem(const QModelIndex &index)
{
    return items.at(index.row());
}
Item* Modules::getItem(int index)
{
    return items.at(index);
}

// SET MODULES
RecipeList::RecipeList(QObject *parent) :
    QAbstractListModel(parent)
{

}
int RecipeList::rowCount(const QModelIndex &) const
{
    return recipes.count();
}
int RecipeList::columnCount(const QModelIndex &) const
{
    return 1;
}
QVariant RecipeList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return recipes.at(index.row())->name;
    case Qt::SizeHintRole:
        return QSize(0,16);
    case Qt::CheckStateRole:
        return recipes.at(index.row())->inclusion;
    default:
        return QVariant();
    }
}
bool RecipeList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch (role)
    {
    case Qt::CheckStateRole:
        recipes.at(index.row())->setInclusion(value.toInt());
        break;
    default:
        break;
    }
    emit dataChanged(this->index(0), this->index(this->recipes.size()));
    return 0;
}
Qt::ItemFlags RecipeList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
int RecipeList::recipesCount()
{
    return recipes.count();
}
void RecipeList::addItemRecipes(Item* item)
{
    beginRemoveRows(QModelIndex(), 0, recipes.count());
    recipes.clear();
    endRemoveRows();

    for (Recipe* i : item->recipes) {
        beginInsertRows(QModelIndex(), recipes.count(), recipes.count());
        recipes.append(i);
        endInsertRows();
    }
}
Recipe* RecipeList::getItemRecipe(int index)
{
    return recipes[index];
}
void RecipeList::swapItemInclusion(const QModelIndex &index)
{
    recipes.at(index.row())->setInclusion(!recipes.at(index.row())->inclusion * 2);
}

long long productionCalculator(ProductionBranch* parent, QList<Item*> *seen, Item *item, double speed)
{
    qDebug() << "Current production: " << item->name;

    ProductionBranch* selectedBranch = new ProductionBranch(item);  // Creates a temporar production line
        // Used to create new branches
    selectedBranch->cost = INT64_MAX;   // The cost is maximum (used to search for most cheap production line)
    ProductionBranch* tempBranch;       // Creates a temporar production line
        // Used to search for cheaper production line from all recipes
    Ingredient* jIngredient;    // used to reference for an Ingredient

    // Search for valid recipes
    for (int i = 0; i < item->recipes.count(); i++)
    {
        // Check if the recipe is available
        if (!item->recipes.at(i)->inclusion)
        {
            continue;
        }
        // Copy recipe into the tempBranch
        tempBranch = new ProductionBranch(item);
        tempBranch->recipe = item->recipes.at(i);
        tempBranch->speed = speed;
        qDebug() << "Current recipe: " <<  tempBranch->recipe->name;

        // Appends items into "seen" list to prevent self-repeating search
        for (int j=0;j<seen->count();j++)
        {
            qDebug() << "Already seen: " << seen->at(j)->name;
            for (int k = 0; k < tempBranch->recipe->ingredients.count(); k++)
            {
                if (seen->at(j) == tempBranch->recipe->ingredients.at(k)->reference)
                {
                    qDebug() << "ABORT: " << tempBranch->recipe->name;
                    tempBranch->cost = INT64_MAX;
                    j = seen->count();
                    break;
                }
            }
        }
        if (tempBranch->cost)
        {
            delete tempBranch;
            continue;
        }
        qDebug() << "Succsessful testing";
        tempBranch->cost = tempBranch->recipe->resCost;

        seen->append(item);
        long long tempCost;
        // Check for the cost
        for (int j = 0;j<tempBranch->recipe->ingredients.count();j++)
        {
            jIngredient = tempBranch->recipe->ingredients.at(j);
            // And search for all the items in recipe2
            tempCost = productionCalculator(tempBranch, seen, jIngredient->reference, speed * (double(jIngredient->quantity) / double(tempBranch->recipe->quantity)));
            if (tempCost == INT64_MAX)
            {
                tempBranch->cost = tempCost;
                break;
            }
            tempCost *= jIngredient->quantity;
            tempBranch->cost += tempCost;
        }
        if (tempBranch->cost != INT64_MAX)
            tempBranch->cost /= tempBranch->recipe->quantity;
        qDebug() << "...cost: " << tempBranch->cost;
        // If the recipe is cheaper than previous, the cheaper one is used in later calculations
        if (tempBranch->cost < selectedBranch->cost)
        {
            delete selectedBranch;
            selectedBranch = new ProductionBranch(*tempBranch);
        }
        delete tempBranch;
        seen->removeLast();
    }
    // Add the recipe into the branch if it's cheap enough
    parent->children.append(selectedBranch);

    return selectedBranch->cost;
}

// Calculation that starts the upper function.
// Started by the USER
void productionCalculator(QTreeWidget* widget, Item *item, double speed)
{
    QList<Item*>* seen = new QList<Item*>;          // Creates "seen" list
    QTreeWidgetItem* thing = new QTreeWidgetItem;   // Creates the ROOT branch

    ProductionBranch* somethingNew = new ProductionBranch();    // Creates the ROOT production line for the Calculation function
    somethingNew->speed = speed;                                // Speed set by USER
    productionCalculator(somethingNew, seen, item, speed);      // Yey, CALCULATIONS! uhh...

    somethingNew->children.at(0)->transformToQTree(thing);      // Convert production line into QTreeWidgetItem
    widget->addTopLevelItem(thing);                             // Add the QTreeWidgetItem into the list
        // Finally shown to the USER!!!
    widget->expandRecursively(widget->indexFromItem(thing));    // EXPAND'N SHOW THE WHOLE BEAUTY OF THE PRODUCTION LINE!
}
