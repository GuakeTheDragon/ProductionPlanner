#include "itemedit.h"
#include "ui_itemedit.h"
//    WIP

DockableWidget::DockableWidget(QWidget *parent, const char *name)
    : QMainWindow(parent)
{
    this->setObjectName(name);
}
DockableWidget::~DockableWidget()
{

}
void DockableWidget::closeEvent(QCloseEvent *event)
{

}
/*void DockableWidget::contextMenuEvent(QContextMenuEvent *event)
{

}
*/
itemEdit::itemEdit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::itemEdit)
{
    ui->setupUi(this);
    ui->tab->setCentralWidget(ui->AvailableMods);
    ui->tab->addDockWidget(Qt::RightDockWidgetArea, ui->dockWidget_2);
    ui->dockWidget_2->setTitleBarWidget(new QWidget());

    ui->tab_2->setCentralWidget(ui->moduleEditFab);
    ui->tab_2->addDockWidget(Qt::RightDockWidgetArea, ui->dockWidget);
    ui->dockWidget->setTitleBarWidget(new QWidget());

    mods = (new AvailableModules);
    proxy = (new QSortFilterProxyModel);
    proxy->setSourceModel(mods);

    ui->moduleEdit->setModel(proxy);
    if (mods->rowCount())
    {
        ui->moduleEdit->selectRow(0);
        ui->toolButtonMinus->setEnabled(true);
    }
    ui->CreatedModsCount->setNum(mods->rowCount());
    ui->tabWidget->setCurrentWidget(new QMainWindow(this));
    //ui->dockWidget->setTitleBarWidget(new QWidget());
}

itemEdit::~itemEdit()
{
    delete ui;
}




/*
QColumnModel::QColumnModel(QObject *parent) :
    QAbstractListModel(parent)
{
    list << 33 << 55 << 77;
}

int QColumnModel::rowCount(const QModelIndex & parent) const
{
    return list.count();
}

QVariant QColumnModel::data(const QModelIndex & index, int role) const
{

}

bool QColumnModel::setData(const QModelIndex & index, const QVariant & value, int role)
{

}

Qt::ItemFlags QColumnModel::flags(const QModelIndex & index) const
{

}

void generateVanillaContentPack()
{
    //QDir dir(".");
    QFile file("test.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "something\n";
        file.close();
    }
}
*/

void itemEdit::on_toolButtonPlus_clicked()
{
    QModelIndex temp = ui->moduleEdit->currentIndex();
    //mods->add(proxy->mapToSource(temp));
    ui->moduleEdit->update();
    (mods->rowCount() == 1 ?
        ui->moduleEdit->setCurrentIndex(ui->moduleEdit->indexAt(QPoint(0,0)))
        : ui->moduleEdit->setCurrentIndex(temp.siblingAtRow(temp.row()+1))
    );
    ui->toolButtonMinus->setEnabled(true);
    ui->CreatedModsCount->setNum(mods->rowCount());
}
void itemEdit::on_toolButtonMinus_clicked()
{
    QModelIndex temp = ui->moduleEdit->currentIndex();
    //mods->remove(proxy->mapToSource(temp));
    ui->moduleEdit->update();
    ui->moduleEdit->setCurrentIndex((temp.siblingAtRow(temp.row()-1).isValid() ?
        temp.siblingAtRow(temp.row()-1)
        : temp.siblingAtRow(0))
    );
    if (!mods->rowCount())
        ui->toolButtonMinus->setEnabled(false);
    ui->CreatedModsCount->setNum(mods->rowCount());
}

