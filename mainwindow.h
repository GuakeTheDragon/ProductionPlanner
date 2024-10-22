#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QCloseEvent>
#include <QSortFilterProxyModel>
#include "satisitem.h"
#include "sqlparser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_itemView_clicked(const QModelIndex &index);

    void on_recipeView_clicked(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_itemView_doubleClicked(const QModelIndex &index);

    void on_recipeView_doubleClicked(const QModelIndex &index);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;

    Modules *itemList;
    RecipeList *recipeList;
    QSortFilterProxyModel* proxy;

    QString DescryptionStyle;
    QString DescryptionStyleTab;
};


#endif // MAINWINDOW_H
