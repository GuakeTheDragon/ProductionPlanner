#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                      // connecting UI
    ui->itemListEdit->setVisible(false);
    ui->tableView->setVisible(false);
    menuBar()->setVisible(false);
    ui->startButton->setEnabled(false);
    ui->removeButton->setEnabled(false);
    ui->tabWidget->setStyleSheet("QTabBar::tab { border: none; margin: 0px; padding: 0px; height: 0px; width: 0px; }");
    ui->dockWidget->setTitleBarWidget(new QWidget());
    ui->dockWidget_2->setTitleBarWidget(new QWidget());

    ui->dockWidget_3->setTitleBarWidget(new QWidget()); // constructing configure area
    ui->dockWidget_5->setTitleBarWidget(new QWidget()); // constructing configure area

    DescryptionStyle = "<p style=\" margin-top:0px; margin-bottom:0px;\">";
    DescryptionStyleTab = "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:10px\">";
/*
    QFile styleF(":/qss/style.css");
    styleF.open(QFile::ReadOnly);           // setup Source File
    if(!styleF.isOpen()) {
        qDebug() << "Error opening QSS\n" << styleF.error();
    }
    QString qssStr = styleF.readAll();          // setup Style Sheet File
    qApp->setStyleSheet(qssStr);
*/

    ContentPackage *baseContent = new ContentPackage();
    QFile file;
    file.setFileName(":/source/modules/vanilla/ContentPack.txt");
    file.open(QFile::ReadOnly);
    //if(!file.isOpen())  {
    //    qDebug() << "Error opening content pack\n" << styleF.error();
    //}
    baseContent->refill(&file);

    itemList = new Modules();
    recipeList = new RecipeList();

    itemList->addContentPack(baseContent);
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
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    productionCalculator(ui->treeWidget, itemList->getItem(proxy->mapToSource(ui->itemView->currentIndex())), ui->quantity->value());
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

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *)
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

