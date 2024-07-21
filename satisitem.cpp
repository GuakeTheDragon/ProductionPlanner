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
int AvailableModules::rowCount(const QModelIndex &parent) const
{
    return list.count();
}
int AvailableModules::columnCount(const QModelIndex &parent) const
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
    /*case Qt::BackgroundRole:
    {
        int temp = list.at(index.row()).value;
        return QColor(255, 255-temp, 255-(temp/2));
    }
    case Qt::ToolTipRole:
        return list.at(index.row()).value;
    case Qt::CheckStateRole:
        return list.at(index.row()).state;*/
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
    //list.insert((index.isValid() ? index.row()+1 : 0), *(new ContentPackage()));
    endInsertRows();
}
void AvailableModules::remove(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    //list.removeAt(index.row());
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
int Modules::rowCount(const QModelIndex &parent) const
{
    return items.count();
}
int Modules::columnCount(const QModelIndex &parent) const
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
    /*case Qt::EditRole:
        switch (index.column())
        {
        case 0:
                return list[index.row()].type;
        case 1:
                return list[index.row()].name;
        case 2:
                return list[index.row()].description;
        }
    case Qt::BackgroundRole:
    {
        int temp = list.at(index.row()).value;
        return QColor(255, 255-temp, 255-(temp/2));
    }
    case Qt::ToolTipRole:
        return list.at(index.row()).value;
    */
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
    //case Qt::EditRole:
        //items.at(index.row())->setInclusion(!items.at(index.row())->inclusion);
    case Qt::CheckStateRole:
        items.at(index.row())->setInclusion(value.toInt());
        break;
    default:
        break;
    }
    emit dataChanged(this->index(0,0), this->index(this->items.size(),0));
}
Qt::ItemFlags Modules::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | /*Qt::ItemIsUserCheckable | Qt::ItemIsEditable |*/ Qt::ItemIsSelectable;
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
    //recipes.append(new Recipe("Name", new Machine(), 10, 10, 10, 10));
}
int RecipeList::rowCount(const QModelIndex &parent) const
{
    return recipes.count();
}
int RecipeList::columnCount(const QModelIndex &parent) const
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
    //case Qt::EditRole:
        //recipes.at(index.row())->setInclusion(!recipes.at(index.row())->inclusion);
    case Qt::CheckStateRole:
        recipes.at(index.row())->setInclusion(value.toInt());
        break;
    default:
        break;
    }
    emit dataChanged(this->index(0), this->index(this->recipes.size()));
}
Qt::ItemFlags RecipeList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | /*Qt::ItemIsUserCheckable |*/ Qt::ItemIsSelectable;
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

    //beginInsertRows(0, item->recipes.count());
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


long long productionCalculator(QTreeWidgetItem* parent, QList<Item*> *seen, Item *item, double speed)
{
    qDebug() << "Current production: " << item->name;
    for (int i=0;i<seen->count();i++)
    {
        if (seen->at(i) == item)
        {
            qDebug() << "ABORT: " << item->name;
            return INT32_MAX;
        }
        qDebug() << "Already seen: " << seen->at(i)->name;
    }
    seen->append(item);
    long long cost = 0;
    long long prevCost = INT64_MAX;
    double actualSpeed;
    QTreeWidgetItem* tempBranch = new QTreeWidgetItem;
    QTreeWidgetItem* current = new QTreeWidgetItem;
    Recipe* iRecipe;
    Ingredient* jIngredient;
    Ingredient* jExcess;
    for (int i=0;i<item->recipes.count();i++)
    {
        iRecipe = item->recipes.at(i);
        qDebug() << "Current recipe: " << iRecipe->name;
        //actualSpeed /= (60 * item->recipes.at(i)->quantity / item->recipes.at(i)->time);
        actualSpeed = speed / (60 * iRecipe->quantity / iRecipe->time);
        cost = iRecipe->resCost;
        if (!iRecipe->inclusion)
        {
            continue;
        }
        //target->addChild(new QTreeWidgetItem);
        for (int j = 0;j<iRecipe->ingredients.count();j++)
        {
            jIngredient = iRecipe->ingredients.at(j);
            //cost += productionCalculator(target->child(j), item->recipes.at(i)->ingredients.at(j)->reference, item->recipes.at(i)->ingredients.at(j)->quantity);
            cost += productionCalculator(tempBranch, seen, jIngredient->reference, (60 * jIngredient->quantity / iRecipe->time) * actualSpeed);
        }
        //cost *= item->recipes.at(i)->time;
        //cost *= quantity;
        cost /= iRecipe->quantity;
        qDebug() << "...cost: " << cost;
        if (cost < prevCost)
        {
            for (int k = 0; current->childCount(); k++)
            {
                current->removeChild(current->takeChild(0));
            }
            delete current;
            current = new QTreeWidgetItem;
            current = tempBranch->clone();
            prevCost = cost;
            QString infoText = "";
            for (int j=0;j<iRecipe->excess.count();j++)
            {
                jExcess = iRecipe->excess.at(j);
                current->setIcon(1, QIcon(QPixmap::fromImage(jExcess->reference->img)));
                infoText += QString::number((60 * jExcess->quantity / iRecipe->time) * actualSpeed, 'g', 5);
                infoText += "/m ";
                infoText += jExcess->reference->name;
                current->setText(1, infoText);
                //if (j < item->recipes.at(i)->excess.count())
                infoText = "";
            }
            current->setIcon(2, QIcon(QPixmap::fromImage(iRecipe->machine->img)));
            infoText += iRecipe->machine->name;
            infoText += ": ";
            infoText += iRecipe->name;
            current->setText(2, infoText);
        }
        for (int k = 0; k < tempBranch->childCount();k++)
        {
            tempBranch->removeChild(0);
        }
        delete tempBranch;
        tempBranch = new QTreeWidgetItem;
    }
    current->setIcon(0, QIcon(QPixmap::fromImage(item->img)));
    QString branchText = "";
    branchText += QString::number(speed, 'g', 5);
    branchText += "/m ";
    branchText += item->name;
    current->setText(0, branchText);
    parent->addChild(current);
    parent->setExpanded(true);

    seen->removeLast();
    return prevCost;
}

long long productionCalculator(ProductionBranch* parent, QList<Item*> *seen, Item *item, double speed)
{
    qDebug() << "Current production: " << item->name;

    ProductionBranch* selectedBranch = new ProductionBranch(item);
    selectedBranch->cost = INT64_MAX;
    ProductionBranch* tempBranch;
    Ingredient* jIngredient;

    for (int i = 0; i < item->recipes.count(); i++)
    {
        if (!item->recipes.at(i)->inclusion)
        {
            continue;
        }
        tempBranch = new ProductionBranch(item);
        tempBranch->recipe = item->recipes.at(i);
        tempBranch->speed = speed;
        qDebug() << "Current recipe: " <<  tempBranch->recipe->name;

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
        for (int j = 0;j<tempBranch->recipe->ingredients.count();j++)
        {
            jIngredient = tempBranch->recipe->ingredients.at(j);
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
        if (tempBranch->cost < selectedBranch->cost)
        {
            delete selectedBranch;
            selectedBranch = new ProductionBranch(*tempBranch);
        }
        delete tempBranch;
        seen->removeLast();
    }
    parent->children.append(selectedBranch);

    return selectedBranch->cost;
}

void productionCalculator(QTreeWidget* widget, Item *item, double speed)
{
    QList<Item*>* seen = new QList<Item*>;
    QTreeWidgetItem* thing = new QTreeWidgetItem;

    ProductionBranch* somethingNew = new ProductionBranch();
    somethingNew->speed = speed;
    productionCalculator(somethingNew, seen, item, speed);

    somethingNew->children.at(0)->transformToQTree(thing);
    widget->addTopLevelItem(thing);

    //productionCalculator(thing, seen, item, speed);
    //QTreeWidgetItem* output = thing->takeChild(0);
    //delete thing;
    //widget->addTopLevelItem(output);
    widget->expandRecursively(widget->indexFromItem(thing));
}
