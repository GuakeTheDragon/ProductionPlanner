#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                      // connecting UI
    item_Edit = new itemEdit(nullptr);
    ui->itemListEdit->setVisible(false);
    ui->tableView->setVisible(false);
    menuBar()->setVisible(false);
    ui->startButton->setEnabled(false);
    ui->removeButton->setEnabled(false);
    //appdata = getenv("APPDATA");
    ui->tab->setCentralWidget(ui->recipeView);  // constructing configure area
    ui->tab->addDockWidget(Qt::LeftDockWidgetArea, ui->dockWidget);
    ui->tab->addDockWidget(Qt::RightDockWidgetArea, ui->dockWidget_2);
    ui->tabWidget->setStyleSheet("QTabBar::tab { border: none; margin: 0px; padding: 0px; height: 0px; width: 0px; }");
    ui->dockWidget->setTitleBarWidget(new QWidget());
    ui->dockWidget_2->setTitleBarWidget(new QWidget());

    QFile styleF(":/qss/style.css");            // setup Source File
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();          // setup Style Sheet File
    qApp->setStyleSheet(qssStr);

    ui->dockWidget_3->setTitleBarWidget(new QWidget()); // constructing configure area
    ui->dockWidget_5->setTitleBarWidget(new QWidget()); // constructing configure area

    DescryptionStyle = "<p style=\" margin-top:0px; margin-bottom:0px;\">";
    DescryptionStyleTab = "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:10px\">";

    ContentPackage *lmao = new ContentPackage();
    QFile file;
    file.setFileName(":/source/modules/vanilla/ContentPack.txt");
    file.open(QFile::ReadOnly);
    file.readLine();                // SourceName
    lmao->name = file.readLine();   // ModuleName
        lmao->name.removeLast(); lmao->name.removeLast();
    /*while text*/file.readLine();  // Description
        //smthg
    /*while end file.readLine();*/   // WIP
        //smthg
    QString img = "";
    QString fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
    while (fileOutput != "%$")          // Adding machines
    {
        img = file.readLine();
        img.removeLast(); img.removeLast();
        lmao->machines.append(new Machine(fileOutput, QImage(QString(":/source/modules/vanilla/machines/%1").arg(img))));
        fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
    }
    fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
    QList<QString> UndefinedItems;
    QList<Ingredient*> UndefinedIngredient;
    while (fileOutput != "%$")          // Adding items
    {
        img = file.readLine();
        img.removeLast(); img.removeLast();
        lmao->items.append(new Item(fileOutput, QImage(QString(":/source/modules/vanilla/icons/%1").arg(img))));
        Item* lastItem = lmao->items.last();
        fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
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
            Recipe* lastRecipe = lastItem->recipes.last();
            lastRecipe->name = fileOutput;
            fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
            lastRecipe->machine = lmao->findMachine(fileOutput);
            fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
            lastRecipe->quantity = fileOutput.toFloat();
            fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
            lastRecipe->time = fileOutput.toDouble();
            fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
            lastRecipe->resCost = fileOutput.toDouble();
            fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
            while (fileOutput != "%$")  // Adding excess
            {
                lastRecipe->excess.append(new Ingredient());
                Ingredient* lastExcess = lastRecipe->excess.last();
                lastExcess->reference = lmao->findItem(fileOutput);
                fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
                lastExcess->quantity = fileOutput.toFloat();
                fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();

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
            fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
            qDebug() << "New recipe: " + lastItem->recipes.last()->name;
            Item* ingr = nullptr;
            while (fileOutput != "%$")  // Adding ingredients
            {
                lastItem->recipes.last()->ingredients.append(new Ingredient());
                Ingredient* lastIngredient = lastItem->recipes.last()->ingredients.last();
                ingr = lmao->findItem(fileOutput);
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
                fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
                lastIngredient->quantity = fileOutput.toFloat();
                fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
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
            fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
        }
        fileOutput = file.readLine(); fileOutput.removeLast(); fileOutput.removeLast();
    }

    itemList = new Modules();
    recipeList = new RecipeList();

    itemList->addContentPack(lmao);
    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(itemList);

    ui->itemView->setModel(proxy);
    ui->recipeView->setModel(recipeList);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->itemListCount->setText(QString("Items: %1").arg(itemList->itemsCount()));

    for (int i =0;i<itemList->itemsCount();i++)
    {
        itemList->swapItemInclusion(itemList->index(i, 0));
    }
    proxy->sort(0);
}

MainWindow::~MainWindow()
{
    delete item_Edit;
    delete ui;
}

void MainWindow::closeEvent (QCloseEvent *)
{
    item_Edit->close();
    //item_Edit->setParent(this);
}

void MainWindow::on_startButton_clicked()
{
    productionCalculator(ui->treeWidget, itemList->getItem(proxy->mapToSource(ui->itemView->currentIndex())), ui->quantity->value());
}

void MainWindow::on_itemListEdit_clicked()
{
    //generateVanillaContentPack();
    if (!item_Edit->isVisible()){
        item_Edit->show();
    }
    item_Edit->activateWindow();
}


void MainWindow::on_itemView_clicked(const QModelIndex &index)
{
    recipeList->addItemRecipes(itemList->getItem(proxy->mapToSource(index)));
    ui->recipeView->update();
    ui->recipeView->clicked(recipeList->index(0));

    ui->itemView->update();
    ui->recipeView->update();
    ui->ingredientView->update();

    ui->startButton->setEnabled(true);
}


void MainWindow::on_recipeView_clicked(const QModelIndex &index)
{
    if (!recipeList->rowCount())
    {
        ui->ingredientView->setText("No recipe!");
        return;
    }

    Recipe* theRecipe = recipeList->getItemRecipe(index.row());
    QString shortDescryption = "";
    shortDescryption += "<b>Result:</b> ";
    shortDescryption += QString::number(theRecipe->quantity, 'g', 5);
    shortDescryption += " " + itemList->getItem(proxy->mapToSource(ui->itemView->currentIndex()))->name;
    // if excess >>
    if (theRecipe->excess.count())
    {
        shortDescryption += DescryptionStyleTab + "<u><i>Excess:</i></u> ";
        for (int i =0;i< theRecipe->excess.count(); i++)
        {
            shortDescryption += DescryptionStyleTab + "x";
            shortDescryption += QString::number(theRecipe->excess.at(i)->quantity, 'g', 5);
            shortDescryption += " " + theRecipe->excess.at(i)->reference->name;
            shortDescryption += ": " + QString::number(double(
                60
                * theRecipe->excess.at(i)->quantity
                / theRecipe->time
                ), 'g', 5) + " /per minute";
        }
    }
    shortDescryption += DescryptionStyle + "<b>Machine:</b> " + theRecipe->machine->name;
    shortDescryption += DescryptionStyle + "<b>Time:</b> " + QString::number(theRecipe->time, 'g', 5) + "s";
    shortDescryption += DescryptionStyle + "<b>Output rate:</b> " + QString::number(double(
        60
        * theRecipe->quantity
        / theRecipe->time
        ), 'g', 5) + " /per minute";
    shortDescryption += DescryptionStyle + "<b><u>Ingredients:</u></b>";
    for (int i=0;i<theRecipe->ingredients.count();i++)
    {
        shortDescryption += DescryptionStyleTab + "x";
        shortDescryption += QString::number(theRecipe->ingredients[i]->quantity, 'g', 5);
        shortDescryption += " " + theRecipe->ingredients[i]->reference->name;
        shortDescryption += ": " + QString::number(double(
            60
            * theRecipe->ingredients[i]->quantity
            / theRecipe->time
            ), 'g', 5) + " /per minute";
    }
    ui->ingredientView->setText(shortDescryption);

    ui->itemView->update();
    ui->recipeView->update();
    ui->ingredientView->update();
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterRegularExpression(arg1);
    ui->itemListCount->setText(QString("Items: %1").arg(proxy->rowCount()));
}


void MainWindow::on_itemView_doubleClicked(const QModelIndex &index)
{
    itemList->swapItemInclusion(proxy->mapToSource(index));
    ui->itemView->update();
    ui->recipeView->update();
    ui->ingredientView->update();
}


void MainWindow::on_recipeView_doubleClicked(const QModelIndex &index)
{
    recipeList->swapItemInclusion(index);
    itemList->getItem(proxy->mapToSource(ui->itemView->currentIndex()))->setInclusion(0);
    {
        bool fullyIncluded = true;
        for (int i=0;i<recipeList->rowCount();i++)
        {
            if (recipeList->getItemRecipe(i)->inclusion)
            {
                itemList->getItem(proxy->mapToSource(ui->itemView->currentIndex()))->setInclusion(1);
            }
            else if (fullyIncluded)
            {
                fullyIncluded = false;
            }
        }
        if (fullyIncluded)
            itemList->getItem(proxy->mapToSource(ui->itemView->currentIndex()))->setInclusion(2);
    }

    ui->itemView->update();
    ui->recipeView->update();
    ui->ingredientView->update();
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (current)
        ui->removeButton->setEnabled(true);
}


void MainWindow::on_removeButton_clicked()
{
    for (int i=0;i<ui->treeWidget->currentItem()->childCount();i++)
        ui->treeWidget->currentItem()->removeChild(0);
    delete ui->treeWidget->currentItem();
    if (!ui->treeWidget->currentItem())
        ui->removeButton->setEnabled(false);
}

