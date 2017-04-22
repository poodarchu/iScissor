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
    QAction *actionZoom_in;
    QAction *actionZoom_Out;
    QAction *actionScissorStart;
    QAction *actionScissorStop;
    QAction *actionScissorUndoLast;

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
        iScissor->setWindowOpacity(1);
        iScissor->setAutoFillBackground(false);
        iScissor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        iScissor->setDocumentMode(false);
        iScissor->setTabShape(QTabWidget::Rounded);

        actionOpen = new QAction(iScissor);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));

        actionSaveContour = new QAction(iScissor);
        actionSaveContour->setObjectName(QStringLiteral("actionSaveContour"));

        actionSaveMask = new QAction(iScissor);
        actionSaveMask->setObjectName(QStringLiteral("actionSaveMask"));

        actionZoom_in = new QAction(iScissor);
        actionZoom_in->setObjectName(QStringLiteral("actionZoom_in"));
        actionZoom_in->setEnabled(false);

        actionZoom_Out = new QAction(iScissor);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        actionZoom_Out->setEnabled(false);

        actionScissorStart = new QAction(iScissor);
        actionScissorStart->setObjectName(QStringLiteral("actionScissorStart"));
        actionScissorStart->setEnabled(false);

        actionScissorStop = new QAction(iScissor);
        actionScissorStop->setObjectName(QStringLiteral("actionScissorStop"));
        actionScissorStop->setEnabled(false);

        actionScissorUndoLast = new QAction(iScissor);
        actionScissorUndoLast->setObjectName(QStringLiteral("actionScissorUndoLast"));
        actionScissorUndoLast->setEnabled(false);

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

        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSaveContour);
        menuFile->addAction(actionSaveMask);

        mainToolBar->addAction(actionZoom_in);
        mainToolBar->addAction(actionZoom_Out);
        mainToolBar->addAction(actionScissorStart);
        mainToolBar->addAction(actionScissorStop);
        mainToolBar->addAction(actionScissorUndoLast);

        retranslateUi(iScissor);

        QMetaObject::connectSlotsByName(iScissor);
    }

    void retranslateUi(QMainWindow *iScissor)
    {
        iScissor->setWindowTitle(QApplication::translate("iScissor", "iScissor", 0));

        actionOpen->setText(QApplication::translate("iScissor", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("iScissor", "Ctrl+O", 0));

        actionSaveContour->setText(QApplication::translate("iScissor", "Save Contour", 0));
        actionSaveContour->setShortcut(QApplication::translate("iScissor", "Ctrl+X", 0));

        actionSaveMask->setText(QApplication::translate("iScissor", "Save Mask", 0));
        actionSaveMask->setShortcut(QApplication::translate("iScissor", "Ctrl+S", 0));

        actionZoom_in->setText(QApplication::translate("iScissor", "放大", 0));

        actionZoom_Out->setText(QApplication::translate("iScissor", "缩小", 0));

        actionScissorStart->setText(QApplication::translate("iScissor", "开始", 0));
#ifndef QT_NO_TOOLTIP
        actionScissorStart->setToolTip(QApplication::translate("iScissor", "开始", 0));
#endif // QT_NO_TOOLTIP

        actionScissorStop->setText(QApplication::translate("iScissor", "完成", 0));
        actionScissorUndoLast->setText(QApplication::translate("iScissor", "撤销", 0));

        label->setText(QApplication::translate("iScissor", "TextLabel", 0));
        menuFile->setTitle(QApplication::translate("iScissor", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class iScissor: public Ui_iScissor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_iScissor_H
