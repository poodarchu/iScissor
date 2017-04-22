#ifndef UI_iScissor_H
#define UI_iScissor_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <ImgLabel.h>

QT_BEGIN_NAMESPACE

class Ui_iScissor
{
public:
    QAction *actionOpen;
    QAction *actionSaveContour;
    QAction *actionSaveMask;
    // QAction *actionExit;
    // QAction *actionUndo;
    // QAction *actionCut;
    // QAction *actionCopy;
    // QAction *actionPaste;
    // QAction *actionOriginal_Image;
    QAction *actionZoom_in;
    QAction *actionZoom_Out;
    QAction *actionScissorStart;
    QAction *actionScissorStop;
    QAction *actionScissorUndoLast;
    // QAction *actionHow_To;
    // QAction *actionAbout;

    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    ImgLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    // QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *iScissor)
    {
        if (iScissor->objectName().isEmpty())
            iScissor->setObjectName(QStringLiteral("iScissor"));
        iScissor->resize(774, 632);
        QIcon icon;
        // icon.addFile(QStringLiteral(":/icon/image/scissor (1).ico"), QSize(), QIcon::Normal, QIcon::Off);
        iScissor->setWindowIcon(icon);
        iScissor->setWindowOpacity(1);
        iScissor->setAutoFillBackground(false);
        iScissor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        iScissor->setDocumentMode(false);
        iScissor->setTabShape(QTabWidget::Rounded);
        // actionNew = new QAction(iScissor);
        // actionNew->setObjectName(QStringLiteral("actionNew"));
        // QIcon icon1;
        // icon1.addFile(QStringLiteral(":/icon/image/new.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionNew->setIcon(icon1);
        actionOpen = new QAction(iScissor);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        // QIcon icon2;
        // icon2.addFile(QStringLiteral(":/icon/image/open_file.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionOpen->setIcon(icon2);
        actionSaveContour = new QAction(iScissor);
        actionSaveContour->setObjectName(QStringLiteral("actionSaveContour"));
        // QIcon icon3;
        // icon3.addFile(QStringLiteral(":/icon/image/save_mask.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionSaveContour->setIcon(icon3);
        actionSaveMask = new QAction(iScissor);
        actionSaveMask->setObjectName(QStringLiteral("actionSaveMask"));
        // QIcon icon4;
        // icon4.addFile(QStringLiteral(":/icon/image/save_counter.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionSaveMask->setIcon(icon4);
        // actionExit = new QAction(iScissor);
        // actionExit->setObjectName(QStringLiteral("actionExit"));
        // QIcon icon5;
        // icon5.addFile(QStringLiteral(":/icon/image/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionExit->setIcon(icon5);
        // actionUndo = new QAction(iScissor);
        // actionUndo->setObjectName(QStringLiteral("actionUndo"));
        // actionCut = new QAction(iScissor);
        // actionCut->setObjectName(QStringLiteral("actionCut"));
        // actionCopy = new QAction(iScissor);
        // actionCopy->setObjectName(QStringLiteral("actionCopy"));
        // actionPaste = new QAction(iScissor);
        // actionPaste->setObjectName(QStringLiteral("actionPaste"));
        // actionOriginal_Image = new QAction(iScissor);
        // actionOriginal_Image->setObjectName(QStringLiteral("actionOriginal_Image"));
        actionZoom_in = new QAction(iScissor);
        actionZoom_in->setObjectName(QStringLiteral("actionZoom_in"));
        actionZoom_in->setEnabled(false);
        // QIcon icon6;
        // icon6.addFile(QStringLiteral(":/icon/image/zoom_in_new.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionZoom_in->setIcon(icon6);
        actionZoom_Out = new QAction(iScissor);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        actionZoom_Out->setEnabled(false);
        // QIcon icon7;
        // icon7.addFile(QStringLiteral(":/icon/image/zoou_out_new.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionZoom_Out->setIcon(icon7);
        actionScissorStart = new QAction(iScissor);
        actionScissorStart->setObjectName(QStringLiteral("actionScissorStart"));
        actionScissorStart->setEnabled(false);
        // QIcon icon8;
        // icon8.addFile(QStringLiteral(":/icon/image/scissor.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionScissorStart->setIcon(icon8);
        actionScissorStop = new QAction(iScissor);
        actionScissorStop->setObjectName(QStringLiteral("actionScissorStop"));
        actionScissorStop->setEnabled(false);
        // QIcon icon9;
        // icon9.addFile(QStringLiteral(":/icon/image/stop.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionScissorStop->setIcon(icon9);
        actionScissorUndoLast = new QAction(iScissor);
        actionScissorUndoLast->setObjectName(QStringLiteral("actionScissorUndoLast"));
        actionScissorUndoLast->setEnabled(false);
        // QIcon icon10;
        // icon10.addFile(QStringLiteral(":/icon/image/undo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        // actionScissorUndoLast->setIcon(icon10);
        // actionHow_To = new QAction(iScissor);
        // actionHow_To->setObjectName(QStringLiteral("actionHow_To"));
        // actionAbout = new QAction(iScissor);
        // actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(iScissor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setEnabled(true);
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1311, 529));
        scrollAreaWidgetContents->setMinimumSize(QSize(1311, 529));
        label = new ImgLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 991, 471));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        iScissor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(iScissor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 774, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
//        menuHelp = new QMenu(menuBar);
//        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        iScissor->setMenuBar(menuBar);
        statusBar = new QStatusBar(iScissor);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        iScissor->setStatusBar(statusBar);
        mainToolBar = new QToolBar(iScissor);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setCursor(QCursor(Qt::ArrowCursor));
        mainToolBar->setMouseTracking(false);
        mainToolBar->setMovable(false);
        iScissor->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        // menuBar->addAction(menuHelp->menuAction());
        // menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSaveContour);
        menuFile->addAction(actionSaveMask);
        // menuFile->addAction(actionExit);
        // menuHelp->addAction(actionHow_To);
        // menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionZoom_in);
        mainToolBar->addAction(actionZoom_Out);
        mainToolBar->addAction(actionScissorStart);
        mainToolBar->addAction(actionScissorStop);
        mainToolBar->addAction(actionScissorUndoLast);

        retranslateUi(iScissor);

        QMetaObject::connectSlotsByName(iScissor);
    } // setupUi

    void retranslateUi(QMainWindow *iScissor)
    {
        iScissor->setWindowTitle(QApplication::translate("iScissor", "iScissor", 0));
        // actionNew->setText(QApplication::translate("iScissor", "New", 0));
        actionOpen->setText(QApplication::translate("iScissor", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("iScissor", "Ctrl+O", 0));
        actionSaveContour->setText(QApplication::translate("iScissor", "Save Contour", 0));
        actionSaveContour->setShortcut(QApplication::translate("iScissor", "Ctrl+X", 0));
        actionSaveMask->setText(QApplication::translate("iScissor", "Save Mask", 0));
        actionSaveMask->setShortcut(QApplication::translate("iScissor", "Ctrl+S", 0));
        // actionExit->setText(QApplication::translate("iScissor", "Exit", 0));
        // actionExit->setShortcut(QApplication::translate("iScissor", "Ctrl+Q", 0));
        // actionUndo->setText(QApplication::translate("iScissor", "Undo", 0));
        // actionCut->setText(QApplication::translate("iScissor", "Cut", 0));
        // actionCopy->setText(QApplication::translate("iScissor", "Copy", 0));
        // actionPaste->setText(QApplication::translate("iScissor", "Paste", 0));
        // actionOriginal_Image->setText(QApplication::translate("iScissor", "Original Image", 0));
        actionZoom_in->setText(QApplication::translate("iScissor", "放大", 0));
        // actionZoom_in->setShortcut(QApplication::translate("iScissor", "Ctrl+=", 0));
        actionZoom_Out->setText(QApplication::translate("iScissor", "缩小", 0));
        // actionZoom_Out->setShortcut(QApplication::translate("iScissor", "Ctrl+-", 0));
        actionScissorStart->setText(QApplication::translate("iScissor", "开始", 0));
#ifndef QT_NO_TOOLTIP
        // actionScissorStart->setToolTip(QApplication::translate("iScissor", "开始", 0));
#endif // QT_NO_TOOLTIP
        actionScissorStop->setText(QApplication::translate("iScissor", "完成", 0));
        actionScissorUndoLast->setText(QApplication::translate("iScissor", "撤销", 0));
        // actionScissorUndoLast->setShortcut(QApplication::translate("iScissor", "Backspace", 0));
        // actionHow_To->setText(QApplication::translate("iScissor", "How To", 0));
        // actionAbout->setText(QApplication::translate("iScissor", "About", 0));
        label->setText(QApplication::translate("iScissor", "TextLabel", 0));
        menuFile->setTitle(QApplication::translate("iScissor", "File", 0));
        // menuHelp->setTitle(QApplication::translate("iScissor", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class iScissor: public Ui_iScissor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_iScissor_H
