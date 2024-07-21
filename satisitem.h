#ifndef SATISITEM_H
#define SATISITEM_H

#include "qtreewidget.h"
#include <QMainWindow>
#include <QAbstractTableModel>
#include <QAbstractListModel>
#include <QList>

// Represents an individual part of each recipe
class Item;
class Ingredient
{
public:
    Item* reference;
    float quantity;

    Ingredient(): reference(nullptr), quantity(0) {};
    Ingredient(Item* ref, float q): reference(ref), quantity(q) {};
    ~Ingredient(){};
};

// Represents a processoring unit
class Machine
{
public:
    QString name;
    QImage img;
    QList<Ingredient*> buildingCost;

    Machine(): name("Unidentified"), img(":/source/img/StockSearchIcon.png"), buildingCost(){};
    Machine(QString n, QImage i): name(n), img(i), buildingCost() {};
    ~Machine(){};
};

// Represents the way an Item is made
class Recipe
{
public:
    QString name;
    Machine* machine;
    float quantity;
    double time, powerConsuption, resCost;
    Qt::CheckState inclusion = Qt::CheckState::Unchecked;
    QList<Ingredient*> ingredients;
    QList<Ingredient*> excess;

    Recipe(): name("A recipe"), machine(), quantity(0), time(0), powerConsuption(0), resCost(0), ingredients() {};
    Recipe(QString n, Machine* m, float q, double t, double pC, double rC): name(n), machine(m), quantity(q), time(t), powerConsuption(pC), resCost(rC), ingredients(), excess() {};
    ~Recipe(){};

    void setInclusion(int i);
};

// Represents an Item
class Item
{
public:
    QString name;
    QImage img;
    Qt::CheckState inclusion = Qt::CheckState::Unchecked;
    QList<Recipe*> recipes;

    Item(): name("An item"), img(":/source/img/StockSearchIcon.png"), recipes(){};
    Item(QString n, QImage i): name(n), img(i), recipes(){};
    ~Item(){};

    void setInclusion(int i);
};

// Represents mods
class ContentPackage
{
public:
    QString name;
    Qt::CheckState inclusion;
    QList<Item*> items;
    QList<Machine*> machines;
    ContentPackage(): name("Unidentified"), items(){};
    ContentPackage(QString n): name(n), items(){};

    void setInclusion(int i);
    Machine* findMachine(QString name);
    Item* findItem(QString name);
};

// Represents Production Line
class ProductionBranch
{
public:
    Item* item;
    Recipe* recipe;
    double speed;
    long long cost;
    QList<ProductionBranch*> children;
    ProductionBranch(): item(), recipe(), speed(1), cost(0), children(){};
    ProductionBranch(ProductionBranch& clone): item(clone.item), recipe(clone.recipe), speed(clone.speed), cost(clone.cost), children(clone.children){};
    ProductionBranch(Item* i): item(i), recipe(), speed(1), cost(0), children(){};
    ~ProductionBranch()
    {
        while(!children.empty())
            children.removeLast();
    }

    void transformToQTree(QTreeWidgetItem* branch);
};

class AvailableMod
{
public:
    QString type, name, description;
    QImage img;
    QString url;
    AvailableMod(): type("Unidentified"), name("Unknown"), description("None."), url(""){};
    AvailableMod(QString t, QString n, QString desc, QString u): type(t), name(n), description(desc), url(u){};
    ~AvailableMod(){};

    void setType(QString str);
    void setName(QString str);
    void setDesc(QString str);
};

class AvailableModules : public QAbstractTableModel
{
    //Q_OBJECT
    QList<AvailableMod> list;
    //friend void productionCalculator();
public:
    explicit AvailableModules(QObject *parent = 0);

    int rowCount(const QModelIndex &index = QModelIndex()) const;
    int columnCount(const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void add(const QModelIndex &index);
    void remove(const QModelIndex &index);
signals:

public slots:

};

// List of included ContentPacks
class Modules : public QAbstractTableModel
{
    //Q_OBJECT
    //friend void productionCalculator();
public:
    explicit Modules(QObject *parent = 0);

    int rowCount(const QModelIndex &index = QModelIndex()) const;
    int columnCount(const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    int itemsCount();
    void addContentPack(ContentPackage* pack);
    void swapItemInclusion(const QModelIndex &index = QModelIndex());
    Item* getItem(const QModelIndex &index = QModelIndex());
    Item* getItem(int index);
private:
    QList<Item*> items;
    QList<Machine*> machines;
signals:

public slots:
};

// List of available recipes for a selected item in Modules
class RecipeList : public QAbstractListModel
{
    //Q_OBJECT
public:
    explicit RecipeList(QObject *parent = 0);

    int rowCount(const QModelIndex &index = QModelIndex()) const;
    int columnCount(const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    int recipesCount();
    void addItemRecipes(Item* item);
    Recipe* getItemRecipe(int index);
    void swapItemInclusion(const QModelIndex &index = QModelIndex());
private:
    QList<Recipe*> recipes;
signals:

public slots:
};

// not included yet
class ProductionLine : public QAbstractTableModel
{
    QList<QTreeWidgetItem> roots;
    friend void productionCalculator();
public:
    explicit ProductionLine(QObject *parent = 0);

    int rowCount(const QModelIndex &index = QModelIndex()) const;
    int columnCount(const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

};

// Actual production planning
long long productionCalculator(QTreeWidgetItem* parent, QList<Item*> *seen, Item *item, double speed);
long long productionCalculator(ProductionBranch* parent, QList<Item*> *seen, Item *item, double speed);
void productionCalculator(QTreeWidget* widget, Item *item, double speed);

#endif // SATISITEM_H
