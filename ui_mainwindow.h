/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_Tree;
    QAction *actionSave_Tree_as;
    QAction *actionAbout;
    QAction *actionHow_to_use;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_7;
    QTableView *tableView;
    QDockWidget *dockWidget_5;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QDoubleSpinBox *quantity;
    QHBoxLayout *horizontalLayout;
    QLabel *lineEditImg;
    QLineEdit *lineEdit;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *itemListCount;
    QPushButton *itemListEdit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QListView *recipeView;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *startButton;
    QPushButton *removeButton;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_4;
    QHBoxLayout *horizontalLayout_5;
    QTextBrowser *ingredientView;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout_4;
    QTableView *itemView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(809, 535);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/source/modules/vanilla/icons/QuantumComputer.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave_Tree = new QAction(MainWindow);
        actionSave_Tree->setObjectName("actionSave_Tree");
        actionSave_Tree_as = new QAction(MainWindow);
        actionSave_Tree_as->setObjectName("actionSave_Tree_as");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionHow_to_use = new QAction(MainWindow);
        actionHow_to_use->setObjectName("actionHow_to_use");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(4, 0, 0, 0);
        treeWidget = new QTreeWidget(centralwidget);
        treeWidget->setObjectName("treeWidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMinimumSize(QSize(64, 64));
        treeWidget->setFocusPolicy(Qt::NoFocus);
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeWidget->setAlternatingRowColors(false);
        treeWidget->setIconSize(QSize(16, 16));
        treeWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        treeWidget->setIndentation(20);
        treeWidget->setRootIsDecorated(false);
        treeWidget->setUniformRowHeights(false);
        treeWidget->setItemsExpandable(true);
        treeWidget->setSortingEnabled(false);
        treeWidget->setAnimated(true);
        treeWidget->setAllColumnsShowFocus(false);
        treeWidget->setWordWrap(false);
        treeWidget->setHeaderHidden(false);
        treeWidget->setExpandsOnDoubleClick(true);
        treeWidget->setColumnCount(3);
        treeWidget->header()->setVisible(true);
        treeWidget->header()->setCascadingSectionResizes(false);
        treeWidget->header()->setMinimumSectionSize(64);
        treeWidget->header()->setDefaultSectionSize(128);
        treeWidget->header()->setHighlightSections(false);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(false));
        treeWidget->header()->setStretchLastSection(true);

        verticalLayout->addWidget(treeWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 809, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        dockWidget_3 = new QDockWidget(MainWindow);
        dockWidget_3->setObjectName("dockWidget_3");
        dockWidget_3->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget_3->setAllowedAreas(Qt::NoDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName("dockWidgetContents_3");
        verticalLayout_7 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(4, 0, 4, 0);
        tableView = new QTableView(dockWidgetContents_3);
        tableView->setObjectName("tableView");
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setMinimumSize(QSize(32, 32));

        verticalLayout_7->addWidget(tableView);

        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_3);
        dockWidget_5 = new QDockWidget(MainWindow);
        dockWidget_5->setObjectName("dockWidget_5");
        dockWidget_5->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget_5->setAllowedAreas(Qt::NoDockWidgetArea);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName("dockWidgetContents_5");
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 4, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(dockWidgetContents_5);
        label->setObjectName("label");
        label->setScaledContents(false);

        verticalLayout_2->addWidget(label);

        quantity = new QDoubleSpinBox(dockWidgetContents_5);
        quantity->setObjectName("quantity");
        quantity->setFocusPolicy(Qt::WheelFocus);
        quantity->setStyleSheet(QString::fromUtf8(""));
        quantity->setWrapping(false);
        quantity->setFrame(true);
        quantity->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        quantity->setAccelerated(true);
        quantity->setKeyboardTracking(true);
        quantity->setProperty("showGroupSeparator", QVariant(false));
        quantity->setMaximum(999999.000000000000000);
        quantity->setValue(1.000000000000000);

        verticalLayout_2->addWidget(quantity);


        verticalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName("horizontalLayout");
        lineEditImg = new QLabel(dockWidgetContents_5);
        lineEditImg->setObjectName("lineEditImg");
        lineEditImg->setMaximumSize(QSize(16, 16));
        lineEditImg->setStyleSheet(QString::fromUtf8(""));
        lineEditImg->setPixmap(QPixmap(QString::fromUtf8(":/source/img/StockSearchIcon.png")));
        lineEditImg->setScaledContents(true);
        lineEditImg->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEditImg);

        lineEdit = new QLineEdit(dockWidgetContents_5);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8(""));
        lineEdit->setDragEnabled(false);
        lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        itemListCount = new QLabel(dockWidgetContents_5);
        itemListCount->setObjectName("itemListCount");
        itemListCount->setMinimumSize(QSize(60, 0));
        itemListCount->setStyleSheet(QString::fromUtf8(""));
        itemListCount->setScaledContents(false);
        itemListCount->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(itemListCount);

        itemListEdit = new QPushButton(dockWidgetContents_5);
        itemListEdit->setObjectName("itemListEdit");
        itemListEdit->setMinimumSize(QSize(30, 20));
        itemListEdit->setMaximumSize(QSize(40, 20));
        itemListEdit->setCursor(QCursor(Qt::PointingHandCursor));
        itemListEdit->setFocusPolicy(Qt::NoFocus);
        itemListEdit->setStyleSheet(QString::fromUtf8(""));
        itemListEdit->setFlat(false);

        horizontalLayout_2->addWidget(itemListEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget = new QTabWidget(dockWidgetContents_5);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setDocumentMode(true);
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        recipeView = new QListView(tab);
        recipeView->setObjectName("recipeView");
        recipeView->setFrameShape(QFrame::NoFrame);
        recipeView->setFrameShadow(QFrame::Plain);
        recipeView->setLineWidth(0);
        recipeView->setSelectionRectVisible(false);

        horizontalLayout_3->addWidget(recipeView);

        tabWidget->addTab(tab, QString());

        verticalLayout_3->addWidget(tabWidget);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        startButton = new QPushButton(dockWidgetContents_5);
        startButton->setObjectName("startButton");
        startButton->setMinimumSize(QSize(0, 24));
        startButton->setCursor(QCursor(Qt::PointingHandCursor));
        startButton->setFocusPolicy(Qt::NoFocus);
        startButton->setStyleSheet(QString::fromUtf8(""));
        startButton->setCheckable(false);
        startButton->setChecked(false);
        startButton->setAutoRepeat(false);
        startButton->setAutoExclusive(false);
        startButton->setAutoDefault(false);
        startButton->setFlat(false);

        horizontalLayout_7->addWidget(startButton);

        removeButton = new QPushButton(dockWidgetContents_5);
        removeButton->setObjectName("removeButton");
        removeButton->setMinimumSize(QSize(0, 24));
        removeButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_7->addWidget(removeButton);


        verticalLayout_4->addLayout(horizontalLayout_7);

        dockWidget_5->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_5);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName("dockWidget_2");
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName("dockWidgetContents_4");
        horizontalLayout_5 = new QHBoxLayout(dockWidgetContents_4);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        ingredientView = new QTextBrowser(dockWidgetContents_4);
        ingredientView->setObjectName("ingredientView");

        horizontalLayout_5->addWidget(ingredientView);

        dockWidget_2->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_2);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName("dockWidget");
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName("dockWidgetContents_2");
        horizontalLayout_4 = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        itemView = new QTableView(dockWidgetContents_2);
        itemView->setObjectName("itemView");
        itemView->setAlternatingRowColors(false);
        itemView->setSelectionMode(QAbstractItemView::SingleSelection);
        itemView->setIconSize(QSize(0, 0));
        itemView->setShowGrid(false);
        itemView->setCornerButtonEnabled(false);
        itemView->horizontalHeader()->setVisible(false);
        itemView->horizontalHeader()->setMinimumSectionSize(30);
        itemView->horizontalHeader()->setHighlightSections(false);
        itemView->horizontalHeader()->setStretchLastSection(true);
        itemView->verticalHeader()->setVisible(false);
        itemView->verticalHeader()->setMinimumSectionSize(16);
        itemView->verticalHeader()->setDefaultSectionSize(16);
        itemView->verticalHeader()->setHighlightSections(false);
        itemView->verticalHeader()->setStretchLastSection(false);

        horizontalLayout_4->addWidget(itemView);

        dockWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_Tree);
        menuFile->addAction(actionSave_Tree_as);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionHow_to_use);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        startButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Production Planner v1.0", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New Tree", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open Tree", nullptr));
        actionSave_Tree->setText(QCoreApplication::translate("MainWindow", "Save Tree", nullptr));
        actionSave_Tree_as->setText(QCoreApplication::translate("MainWindow", "Save Tree as...", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionHow_to_use->setText(QCoreApplication::translate("MainWindow", "How to use", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Other information", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Excess", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Production line", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Quantity", nullptr));
        quantity->setSuffix(QCoreApplication::translate("MainWindow", " items/min", nullptr));
        lineEditImg->setText(QString());
#if QT_CONFIG(tooltip)
        lineEdit->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Supports <span style=\" font-weight:700;\">Reg</span>ular <span style=\" font-weight:700;\">Ex</span>pressions</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit->setInputMask(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search for item", nullptr));
        itemListCount->setText(QCoreApplication::translate("MainWindow", "Items: 0", nullptr));
        itemListEdit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        ingredientView->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
