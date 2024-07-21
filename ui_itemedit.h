/********************************************************************************
** Form generated from reading UI file 'itemedit.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMEDIT_H
#define UI_ITEMEDIT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "itemedit.h"

QT_BEGIN_NAMESPACE

class Ui_itemEdit
{
public:
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *tabWidget;
    DockableWidget *tab;
    QHBoxLayout *horizontalLayout;
    QFrame *AvailableMods;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QTableWidget *tableWidget;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *ModDescription;
    DockableWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QFrame *moduleEditFab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *searchLine;
    QHBoxLayout *horizontalLayout_7;
    QLabel *CreatedModsLabel;
    QLabel *CreatedModsCount;
    QTableView *moduleEdit;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *toolButtonPlus;
    QToolButton *toolButtonMinus;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_8;
    QColumnView *columnView;

    void setupUi(QDialog *itemEdit)
    {
        if (itemEdit->objectName().isEmpty())
            itemEdit->setObjectName("itemEdit");
        itemEdit->resize(817, 545);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(itemEdit->sizePolicy().hasHeightForWidth());
        itemEdit->setSizePolicy(sizePolicy);
        itemEdit->setMinimumSize(QSize(200, 150));
        itemEdit->setBaseSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/source/modules/vanilla/icons/AssemblyDirectorSystem.png"), QSize(), QIcon::Normal, QIcon::Off);
        itemEdit->setWindowIcon(icon);
        itemEdit->setStyleSheet(QString::fromUtf8(""));
        itemEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        horizontalLayout_5 = new QHBoxLayout(itemEdit);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(itemEdit);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new DockableWidget();
        tab->setObjectName("tab");
        tab->setMouseTracking(false);
        tab->setStyleSheet(QString::fromUtf8("color: #AAA;"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        AvailableMods = new QFrame(tab);
        AvailableMods->setObjectName("AvailableMods");
        sizePolicy.setHeightForWidth(AvailableMods->sizePolicy().hasHeightForWidth());
        AvailableMods->setSizePolicy(sizePolicy);
        AvailableMods->setFrameShape(QFrame::StyledPanel);
        AvailableMods->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(AvailableMods);
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(AvailableMods);
        label_5->setObjectName("label_5");
        label_5->setMaximumSize(QSize(16, 16));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/source/img/StockSearchIcon.png")));
        label_5->setScaledContents(true);

        horizontalLayout_4->addWidget(label_5);

        lineEdit_3 = new QLineEdit(AvailableMods);
        lineEdit_3->setObjectName("lineEdit_3");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        lineEdit_3->setStyleSheet(QString::fromUtf8(""));
        lineEdit_3->setDragEnabled(false);
        lineEdit_3->setClearButtonEnabled(false);

        horizontalLayout_4->addWidget(lineEdit_3);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label = new QLabel(AvailableMods);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(label);

        tableWidget = new QTableWidget(AvailableMods);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignBottom);
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignLeading|Qt::AlignBottom);
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignLeading|Qt::AlignBottom);
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem14);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy2);
        tableWidget->setTabletTracking(false);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setStyleSheet(QString::fromUtf8(""));
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        tableWidget->setAutoScroll(true);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setDragEnabled(false);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setTextElideMode(Qt::ElideLeft);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setShowGrid(true);
        tableWidget->setSortingEnabled(true);
        tableWidget->setWordWrap(true);
        tableWidget->setCornerButtonEnabled(false);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(18);
        tableWidget->verticalHeader()->setDefaultSectionSize(18);
        tableWidget->verticalHeader()->setHighlightSections(true);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout_5->addWidget(tableWidget);


        verticalLayout_4->addLayout(verticalLayout_5);


        horizontalLayout->addWidget(AvailableMods);

        dockWidget_2 = new QDockWidget(tab);
        dockWidget_2->setObjectName("dockWidget_2");
        dockWidget_2->setMinimumSize(QSize(70, 89));
        dockWidget_2->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget_2->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName("dockWidgetContents_2");
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ModDescription = new QTextBrowser(dockWidgetContents_2);
        ModDescription->setObjectName("ModDescription");
        sizePolicy.setHeightForWidth(ModDescription->sizePolicy().hasHeightForWidth());
        ModDescription->setSizePolicy(sizePolicy);
        ModDescription->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(ModDescription);

        dockWidget_2->setWidget(dockWidgetContents_2);

        horizontalLayout->addWidget(dockWidget_2);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/source/modules/vanilla/icons/SpelevatorPart_5.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon1, QString());
        tab_2 = new DockableWidget();
        tab_2->setObjectName("tab_2");
        tab_2->setEnabled(false);
        tab_2->setStyleSheet(QString::fromUtf8("color: #AAA;"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        moduleEditFab = new QFrame(tab_2);
        moduleEditFab->setObjectName("moduleEditFab");
        moduleEditFab->setFrameShape(QFrame::StyledPanel);
        moduleEditFab->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(moduleEditFab);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 4);
        label_4 = new QLabel(moduleEditFab);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(16, 16));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/source/img/StockSearchIcon.png")));
        label_4->setScaledContents(true);

        horizontalLayout_2->addWidget(label_4);

        searchLine = new QLineEdit(moduleEditFab);
        searchLine->setObjectName("searchLine");
        searchLine->setStyleSheet(QString::fromUtf8(""));
        searchLine->setDragEnabled(false);
        searchLine->setClearButtonEnabled(false);

        horizontalLayout_2->addWidget(searchLine);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(4);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        CreatedModsLabel = new QLabel(moduleEditFab);
        CreatedModsLabel->setObjectName("CreatedModsLabel");
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(CreatedModsLabel->sizePolicy().hasHeightForWidth());
        CreatedModsLabel->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(CreatedModsLabel);

        CreatedModsCount = new QLabel(moduleEditFab);
        CreatedModsCount->setObjectName("CreatedModsCount");

        horizontalLayout_7->addWidget(CreatedModsCount);


        verticalLayout_3->addLayout(horizontalLayout_7);

        moduleEdit = new QTableView(moduleEditFab);
        moduleEdit->setObjectName("moduleEdit");
        moduleEdit->setFocusPolicy(Qt::NoFocus);
        moduleEdit->setSelectionMode(QAbstractItemView::SingleSelection);
        moduleEdit->setSelectionBehavior(QAbstractItemView::SelectRows);
        moduleEdit->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        moduleEdit->setSortingEnabled(true);
        moduleEdit->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        moduleEdit->horizontalHeader()->setStretchLastSection(true);
        moduleEdit->verticalHeader()->setVisible(false);
        moduleEdit->verticalHeader()->setHighlightSections(false);

        verticalLayout_3->addWidget(moduleEdit);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        toolButtonPlus = new QToolButton(moduleEditFab);
        toolButtonPlus->setObjectName("toolButtonPlus");
        toolButtonPlus->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/source/img/stylesheet-plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonPlus->setIcon(icon2);

        horizontalLayout_6->addWidget(toolButtonPlus);

        toolButtonMinus = new QToolButton(moduleEditFab);
        toolButtonMinus->setObjectName("toolButtonMinus");
        toolButtonMinus->setEnabled(false);
        toolButtonMinus->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/source/img/stylesheet-minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonMinus->setIcon(icon3);

        horizontalLayout_6->addWidget(toolButtonMinus);


        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout_3->addWidget(moduleEditFab);

        dockWidget = new QDockWidget(tab_2);
        dockWidget->setObjectName("dockWidget");
        dockWidget->setFloating(false);
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        horizontalLayout_8 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        columnView = new QColumnView(dockWidgetContents);
        columnView->setObjectName("columnView");

        horizontalLayout_8->addWidget(columnView);

        dockWidget->setWidget(dockWidgetContents);

        horizontalLayout_3->addWidget(dockWidget);

        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/source/modules/vanilla/icons/ConversionCube.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_2, icon4, QString());

        horizontalLayout_5->addWidget(tabWidget);


        retranslateUi(itemEdit);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(itemEdit);
    } // setupUi

    void retranslateUi(QDialog *itemEdit)
    {
        itemEdit->setWindowTitle(QCoreApplication::translate("itemEdit", "Item Editor", nullptr));
        label_5->setText(QString());
        lineEdit_3->setInputMask(QString());
        lineEdit_3->setText(QString());
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("itemEdit", "Search for item", nullptr));
        label->setText(QCoreApplication::translate("itemEdit", "Available Modules: 3", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("itemEdit", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("itemEdit", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("itemEdit", "Descryption", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("itemEdit", "Satisfactory", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("itemEdit", "CoalMod", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("itemEdit", "Coal recepies", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(1, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("itemEdit", "Factorio", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(1, 1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("itemEdit", "OceanMod", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(1, 2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("itemEdit", "Mode oil", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(2, 0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("itemEdit", "Minecraft", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(2, 1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("itemEdit", "OsmiumMod", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(2, 2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("itemEdit", "Gas material", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        ModDescription->setHtml(QCoreApplication::translate("itemEdit", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("itemEdit", "Modules", nullptr));
        label_4->setText(QString());
        searchLine->setInputMask(QString());
        searchLine->setText(QString());
        searchLine->setPlaceholderText(QCoreApplication::translate("itemEdit", "Search for item", nullptr));
        CreatedModsLabel->setText(QCoreApplication::translate("itemEdit", "Created Modules:", nullptr));
        CreatedModsCount->setText(QCoreApplication::translate("itemEdit", "0", nullptr));
        toolButtonPlus->setText(QString());
        toolButtonMinus->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("itemEdit", "Module Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class itemEdit: public Ui_itemEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMEDIT_H
