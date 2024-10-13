#ifndef SATISITEM_H
#define SATISITEM_H

#include "qtreewidget.h"        // I don't remember for what is it states here
#include <QMainWindow>          // Same
#include <QAbstractTableModel>  // Essential for Model-View tables
#include <QAbstractListModel>   // Essential for Model-View lists
#include <QList>                // To use QLists of Qt

class Item;
// Represents an individual part of each recipe
class Ingredient
{
public:
    Item* reference;    // Ref for the item, represented by RECIPE.
    float quantity;     // Amount of the item, used by RECIPE.

    Ingredient(): reference(nullptr), quantity(0) {};
    Ingredient(Item* ref, float q): reference(ref), quantity(q) {};
    ~Ingredient(){};
};

// Represents a processoring unit
class Machine
{
public:
    QString name;                       // Name of the machine.
    QImage img;                         // Image shown in the program.
    QList<Ingredient*> buildingCost;    // (WIP) Amount of ingredients used to build the machine.

    Machine(): name("Unidentified"), img(":/source/img/StockSearchIcon.png"), buildingCost(){};
    Machine(QString n, QImage i): name(n), img(i), buildingCost() {};
    ~Machine(){};
};

// Represents the way an Item is made
class Recipe
{
public:
    QString name;                           // Recipe has a name. Each item can have different recipes.
    Machine* machine;                       // The machine where the RECIPE is processed.
    float quantity;                         // Amount of ITEMS made by the RECIPE.
    double time, powerConsuption, resCost;  // time used to process whole the RECIPE;
                                            // (WIP) powerConsuption - how much power used to run the machine;
                                            // resCost - total cost of the RECIPE (OBSOLETE).
    Qt::CheckState inclusion = Qt::CheckState::Unchecked;   // Used to include/exclude the recipe from further calculations.
    QList<Ingredient*> ingredients;         // QList of refs to ingredients (items and quantity used by the RECIPE).
    QList<Ingredient*> excess;              // Excess/Additional items made by the RECIPE.

    Recipe(): name("A recipe"), machine(), quantity(0), time(0), powerConsuption(0), resCost(0), ingredients() {};
    Recipe(QString n, Machine* m, float q, double t, double pC, double rC): name(n), machine(m), quantity(q), time(t), powerConsuption(pC), resCost(rC), ingredients(), excess() {};
    ~Recipe(){};

    void setInclusion(int i);               // Is the RECIPE used in calculations? Yes/No
};

// Represents an Item
class Item
{
public:
    QString name;               // Name of the item.
    QImage img;                 // Image of the item, shown in the program. All images are 256x256px, but compressed into 16x16px or 32x32px
    Qt::CheckState inclusion = Qt::CheckState::Unchecked;   // Include/Exclude item from further calculations (like it doesn't exist).
    QList<Recipe*> recipes;     // Recipes used to MAKE the ITEM

    Item(): name("An item"), img(":/source/img/StockSearchIcon.png"), recipes(){};
    Item(QString n, QImage i): name(n), img(i), recipes(){};
    ~Item(){};

    void setInclusion(int i);   // Include/Exclude? yes/no
};

// Represents mods
// Contains ITEMs (+RECIPEs, +INGREDIENTs), MACHINEs and IMAGEs for them. All in once.
class ContentPackage
{
public:
    QString name;                       // Name of the content pack
    Qt::CheckState inclusion;           // Included/Excluded in programm calculations
    QList<Item*> items;                 // What ITEMs the content pack has
    QList<Machine*> machines;           // And what MACHINEs is has
    ContentPackage(): name("Unidentified"), items(){};
    ContentPackage(QString n): name(n), items(){};

    void setInclusion(int i);           // Include/Exclude? Yes/No
    Machine* findMachine(QString name); // Returns reference of the machine, searched for by the name.
    Item* findItem(QString name);       // Return reference of the item, searched for by the name.
};

// Represents Production Line
// Used to calculate the production line of an item
// Has methods and some essential data to hold for later convertation into QTreeWidgetItem
class ProductionBranch
{
public:
    Item* item;     // What item is produced at this branch right now
    Recipe* recipe; // What recipe it uses right now
    double speed;   // How much by minute
    long long cost; // How much it costs right now
    QList<ProductionBranch*> children;  // Usually children are INGREDIENTs of the used RECIPE of this ITEM
    ProductionBranch(): item(), recipe(), speed(1), cost(0), children(){};
    ProductionBranch(ProductionBranch& clone): item(clone.item), recipe(clone.recipe), speed(clone.speed), cost(clone.cost), children(clone.children){};
    ProductionBranch(Item* i): item(i), recipe(), speed(1), cost(0), children(){};
    ~ProductionBranch()
    {
        while(!children.empty())
            children.removeLast();
    }

    void transformToQTree(QTreeWidgetItem* branch);
    // I don't remember exactly why I created this class instead of using QTreeWidgetItem by first.
    // It had some troubles in placing and/or creating branches in program.
};

// WIP
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

// (WIP) I don't remember what is this
// Most probably used for the list of mods already included in program by deafult
// The functionality of this feature is hidden due to being unfinished
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
// It's the list of ITEMs, visible on the start of the program.
class Modules : public QAbstractTableModel
{
    //Q_OBJECT
    //friend void productionCalculator();
public:
    explicit Modules(QObject *parent = 0);  // don't remember what is this for
                                            // Program had several troubles during build with the lack of it
    int rowCount(const QModelIndex &index = QModelIndex()) const;                               // Must be defined
    int columnCount(const QModelIndex &index = QModelIndex()) const;                            // Must be defined
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;                  // Must be defined
    bool setData(const QModelIndex &index, const QVariant & value, int role = Qt::EditRole);    // Must be defined
    Qt::ItemFlags flags(const QModelIndex &index) const;                                        // Must be defined

    int itemsCount();                           // Amount of ITEMs shown right now
    void addContentPack(ContentPackage* pack);  // What content packs are used to fill the QList of items
    void swapItemInclusion(const QModelIndex &index = QModelIndex());   // Include/Exclude? Yes/No
    Item* getItem(const QModelIndex &index = QModelIndex());    // Used to reference an item by Index of Selected row
    Item* getItem(int index);
private:
    QList<Item*> items;         // All items
    QList<Machine*> machines;   // All machines (aren't shown. Used for calculation)
signals:

public slots:
};

// List of available recipes for a selected item in Modules
// Shown in program when the USER selects an ITEM from the list
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

// (WIP) not included yet
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
// arg QTreeWidgetItem is (most probably) OBSOLETE and never be used.
long long productionCalculator(QTreeWidgetItem* parent, QList<Item*> *seen, Item *item, double speed);
// This is what actually used
// returns the COST of the production line
long long productionCalculator(ProductionBranch* parent, QList<Item*> *seen, Item *item, double speed);
// Used to start the calculations by the USER
void productionCalculator(QTreeWidget* widget, Item *item, double speed);

#endif // SATISITEM_H
