#ifndef ITEMEDIT_H
#define ITEMEDIT_H
//    WIP.
//    #include <QtXml>
//    #include <QDir>
//    #include <QAbstractItemModel>
//    #include <QAbstractListModel>
#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QSortFilterProxyModel>
#include "satisitem.h"


QT_BEGIN_NAMESPACE
namespace Ui { class itemEdit; }
QT_END_NAMESPACE

class itemEdit : public QDialog
{
    Q_OBJECT

public:
    explicit itemEdit(QWidget *parent = nullptr);
    ~itemEdit();
    AvailableModules* mods;
    QSortFilterProxyModel* proxy;

private slots:
    void on_toolButtonPlus_clicked();

    void on_toolButtonMinus_clicked();

private:
    Ui::itemEdit *ui;
};



class DockableWidget : public QMainWindow
{
    Q_OBJECT

public:
    DockableWidget(QWidget *parent = 0, const char *name = 0);
    ~DockableWidget();

protected:
    void closeEvent(QCloseEvent *event);
    //void contextMenuEvent(QContextMenuEvent *event);
};

/*
class QColumnModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QColumnModel(QObject *parent = 0);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex & index) const;
private:
    QList<int> list;
};
*/
//void generateVanillaContentPack();

#endif // ITEMEDIT_H
