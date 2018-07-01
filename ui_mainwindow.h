/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbrirVideo;
    QAction *actionToolLine;
    QAction *actionToolArrow;
    QAction *actionToolRectangle;
    QAction *actionToolCircle;
    QAction *actionToolPolygon;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QWidget *tab2;
    QGraphicsView *graphicsView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPath;
    QLineEdit *videoEdit;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *alternativeViewSelector;
    QGraphicsView *graphicsViewAlternative;
    QSlider *slider;
    QGroupBox *configBox;
    QToolBox *toolBox;
    QWidget *page;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkShowPoint;
    QCheckBox *checkShowRect;
    QCheckBox *checkShowContour;
    QCheckBox *checkShowMovement;
    QCheckBox *chechShowId;
    QCheckBox *checkShowTrack;
    QCheckBox *checkShowDistance;
    QWidget *page_5;
    QGraphicsView *graphicsViewBackground;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QSpinBox *nSamples;
    QPushButton *btnSetBackground;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btnSetFrameBackground;
    QWidget *page_4;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelPixelsPerMeter;
    QPushButton *btnMeassure;
    QWidget *page_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnZoneGlobal;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QWidget *page_3;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAnimalSelect;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QPushButton *pushButton_6;
    QWidget *pageAnalysis;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkCreateTrackMap;
    QFrame *confirmBox;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *confirmLayout;
    QPushButton *btnConfirm;
    QPushButton *btnCancel;
    QPushButton *btnResetTrack;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QPushButton *btnStartTimeSetInstant;
    QPushButton *btnEndTimeSetInstant;
    QLabel *label_5;
    QTimeEdit *startTime;
    QTimeEdit *endTime;
    QProgressBar *progressBar;
    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *nextBtn;
    QFrame *playerControls;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *playerControlsLayout;
    QPushButton *btnPlayPause;
    QSlider *framePosSlider;
    QLabel *labelTime;
    QFrame *adjustBox;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_9;
    QSlider *adjustSlider;
    QWidget *tab3;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 608);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionAbrirVideo = new QAction(MainWindow);
        actionAbrirVideo->setObjectName(QStringLiteral("actionAbrirVideo"));
        actionToolLine = new QAction(MainWindow);
        actionToolLine->setObjectName(QStringLiteral("actionToolLine"));
        actionToolLine->setCheckable(true);
        actionToolArrow = new QAction(MainWindow);
        actionToolArrow->setObjectName(QStringLiteral("actionToolArrow"));
        actionToolArrow->setCheckable(true);
        actionToolRectangle = new QAction(MainWindow);
        actionToolRectangle->setObjectName(QStringLiteral("actionToolRectangle"));
        actionToolRectangle->setCheckable(true);
        actionToolCircle = new QAction(MainWindow);
        actionToolCircle->setObjectName(QStringLiteral("actionToolCircle"));
        actionToolCircle->setCheckable(true);
        actionToolPolygon = new QAction(MainWindow);
        actionToolPolygon->setObjectName(QStringLiteral("actionToolPolygon"));
        actionToolPolygon->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1001, 551));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        graphicsView = new QGraphicsView(tab2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(240, 11, 400, 300));
        graphicsView->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 127);"));
        horizontalLayoutWidget = new QWidget(tab2);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(240, 440, 401, 22));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labelPath = new QLabel(horizontalLayoutWidget);
        labelPath->setObjectName(QStringLiteral("labelPath"));

        horizontalLayout->addWidget(labelPath);

        videoEdit = new QLineEdit(horizontalLayoutWidget);
        videoEdit->setObjectName(QStringLiteral("videoEdit"));

        horizontalLayout->addWidget(videoEdit);

        verticalLayoutWidget_2 = new QWidget(tab2);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(650, 10, 341, 331));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        alternativeViewSelector = new QComboBox(verticalLayoutWidget_2);
        alternativeViewSelector->setObjectName(QStringLiteral("alternativeViewSelector"));

        verticalLayout_2->addWidget(alternativeViewSelector);

        graphicsViewAlternative = new QGraphicsView(verticalLayoutWidget_2);
        graphicsViewAlternative->setObjectName(QStringLiteral("graphicsViewAlternative"));

        verticalLayout_2->addWidget(graphicsViewAlternative);

        slider = new QSlider(verticalLayoutWidget_2);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(slider);

        configBox = new QGroupBox(tab2);
        configBox->setObjectName(QStringLiteral("configBox"));
        configBox->setGeometry(QRect(10, 10, 221, 451));
        configBox->setStyleSheet(QStringLiteral(""));
        toolBox = new QToolBox(configBox);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(0, 20, 221, 431));
        toolBox->setStyleSheet(QStringLiteral(""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 221, 269));
        verticalLayoutWidget = new QWidget(page);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 221, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkShowPoint = new QCheckBox(verticalLayoutWidget);
        checkShowPoint->setObjectName(QStringLiteral("checkShowPoint"));
        checkShowPoint->setChecked(true);

        verticalLayout->addWidget(checkShowPoint);

        checkShowRect = new QCheckBox(verticalLayoutWidget);
        checkShowRect->setObjectName(QStringLiteral("checkShowRect"));
        checkShowRect->setChecked(true);

        verticalLayout->addWidget(checkShowRect);

        checkShowContour = new QCheckBox(verticalLayoutWidget);
        checkShowContour->setObjectName(QStringLiteral("checkShowContour"));
        checkShowContour->setChecked(false);

        verticalLayout->addWidget(checkShowContour);

        checkShowMovement = new QCheckBox(verticalLayoutWidget);
        checkShowMovement->setObjectName(QStringLiteral("checkShowMovement"));

        verticalLayout->addWidget(checkShowMovement);

        chechShowId = new QCheckBox(verticalLayoutWidget);
        chechShowId->setObjectName(QStringLiteral("chechShowId"));
        chechShowId->setChecked(false);

        verticalLayout->addWidget(chechShowId);

        checkShowTrack = new QCheckBox(verticalLayoutWidget);
        checkShowTrack->setObjectName(QStringLiteral("checkShowTrack"));
        checkShowTrack->setChecked(true);

        verticalLayout->addWidget(checkShowTrack);

        checkShowDistance = new QCheckBox(verticalLayoutWidget);
        checkShowDistance->setObjectName(QStringLiteral("checkShowDistance"));
        checkShowDistance->setEnabled(false);
        checkShowDistance->setChecked(false);

        verticalLayout->addWidget(checkShowDistance);

        toolBox->addItem(page, QStringLiteral("Visualizar"));
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        page_5->setGeometry(QRect(0, 0, 221, 269));
        graphicsViewBackground = new QGraphicsView(page_5);
        graphicsViewBackground->setObjectName(QStringLiteral("graphicsViewBackground"));
        graphicsViewBackground->setGeometry(QRect(10, 0, 200, 150));
        horizontalLayoutWidget_5 = new QWidget(page_5);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 160, 201, 31));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_6);

        nSamples = new QSpinBox(horizontalLayoutWidget_5);
        nSamples->setObjectName(QStringLiteral("nSamples"));
        nSamples->setMaximum(200);
        nSamples->setValue(15);

        horizontalLayout_8->addWidget(nSamples);

        btnSetBackground = new QPushButton(horizontalLayoutWidget_5);
        btnSetBackground->setObjectName(QStringLiteral("btnSetBackground"));

        horizontalLayout_8->addWidget(btnSetBackground);

        horizontalLayoutWidget_7 = new QWidget(page_5);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(10, 200, 201, 31));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        btnSetFrameBackground = new QPushButton(horizontalLayoutWidget_7);
        btnSetFrameBackground->setObjectName(QStringLiteral("btnSetFrameBackground"));

        horizontalLayout_9->addWidget(btnSetFrameBackground);

        toolBox->addItem(page_5, QStringLiteral("Background"));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setGeometry(QRect(0, 0, 221, 269));
        label_4 = new QLabel(page_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 0, 91, 20));
        label_4->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_6 = new QWidget(page_4);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(0, 20, 221, 31));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        labelPixelsPerMeter = new QLabel(horizontalLayoutWidget_6);
        labelPixelsPerMeter->setObjectName(QStringLiteral("labelPixelsPerMeter"));
        labelPixelsPerMeter->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(labelPixelsPerMeter);

        btnMeassure = new QPushButton(horizontalLayoutWidget_6);
        btnMeassure->setObjectName(QStringLiteral("btnMeassure"));

        horizontalLayout_6->addWidget(btnMeassure);

        toolBox->addItem(page_4, QString::fromUtf8("Op\303\247\303\265es"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 221, 269));
        verticalLayoutWidget_3 = new QWidget(page_2);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(5, 0, 211, 250));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnZoneGlobal = new QPushButton(verticalLayoutWidget_3);
        btnZoneGlobal->setObjectName(QStringLiteral("btnZoneGlobal"));

        horizontalLayout_3->addWidget(btnZoneGlobal);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer);

        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(verticalLayoutWidget_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_3->addWidget(comboBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_3 = new QPushButton(verticalLayoutWidget_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(verticalLayoutWidget_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_2);

        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        comboBox_2 = new QComboBox(verticalLayoutWidget_3);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        verticalLayout_3->addWidget(comboBox_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_4 = new QPushButton(verticalLayoutWidget_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_5->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(verticalLayoutWidget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_5->addWidget(pushButton_5);


        verticalLayout_3->addLayout(horizontalLayout_5);

        toolBox->addItem(page_2, QStringLiteral("Zonas"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 98, 28));
        horizontalLayoutWidget_4 = new QWidget(page_3);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(0, 0, 221, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnAnimalSelect = new QPushButton(horizontalLayoutWidget_4);
        btnAnimalSelect->setObjectName(QStringLiteral("btnAnimalSelect"));

        horizontalLayout_2->addWidget(btnAnimalSelect);

        pushButton = new QPushButton(horizontalLayoutWidget_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        groupBox = new QGroupBox(page_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 50, 221, 141));
        horizontalLayoutWidget_8 = new QWidget(groupBox);
        horizontalLayoutWidget_8->setObjectName(QStringLiteral("horizontalLayoutWidget_8"));
        horizontalLayoutWidget_8->setGeometry(QRect(0, 20, 221, 41));
        horizontalLayout_11 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(horizontalLayoutWidget_8);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_11->addWidget(label_8);

        lineEdit = new QLineEdit(horizontalLayoutWidget_8);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_11->addWidget(lineEdit);

        pushButton_6 = new QPushButton(horizontalLayoutWidget_8);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_11->addWidget(pushButton_6);

        toolBox->addItem(page_3, QStringLiteral("Cobaia"));
        pageAnalysis = new QWidget();
        pageAnalysis->setObjectName(QStringLiteral("pageAnalysis"));
        pageAnalysis->setGeometry(QRect(0, 0, 98, 28));
        verticalLayoutWidget_4 = new QWidget(pageAnalysis);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(0, 0, 211, 31));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        checkCreateTrackMap = new QCheckBox(verticalLayoutWidget_4);
        checkCreateTrackMap->setObjectName(QStringLiteral("checkCreateTrackMap"));

        verticalLayout_4->addWidget(checkCreateTrackMap);

        toolBox->addItem(pageAnalysis, QString::fromUtf8("An\303\241lise"));
        confirmBox = new QFrame(tab2);
        confirmBox->setObjectName(QStringLiteral("confirmBox"));
        confirmBox->setGeometry(QRect(340, 340, 191, 41));
        confirmBox->setFrameShape(QFrame::StyledPanel);
        confirmBox->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_3 = new QWidget(confirmBox);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 0, 171, 41));
        confirmLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        confirmLayout->setSpacing(6);
        confirmLayout->setContentsMargins(11, 11, 11, 11);
        confirmLayout->setObjectName(QStringLiteral("confirmLayout"));
        confirmLayout->setContentsMargins(0, 0, 0, 0);
        btnConfirm = new QPushButton(horizontalLayoutWidget_3);
        btnConfirm->setObjectName(QStringLiteral("btnConfirm"));
        btnConfirm->setEnabled(true);
        btnConfirm->setMouseTracking(false);
        btnConfirm->setAutoFillBackground(true);
        btnConfirm->setStyleSheet(QStringLiteral("color: rgb(0, 170, 0);"));
        btnConfirm->setAutoDefault(false);
        btnConfirm->setFlat(false);

        confirmLayout->addWidget(btnConfirm);

        btnCancel = new QPushButton(horizontalLayoutWidget_3);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setEnabled(true);
        btnCancel->setMouseTracking(false);
        btnCancel->setAutoFillBackground(false);
        btnCancel->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        btnCancel->setAutoDefault(false);
        btnCancel->setFlat(false);

        confirmLayout->addWidget(btnCancel);

        btnResetTrack = new QPushButton(tab2);
        btnResetTrack->setObjectName(QStringLiteral("btnResetTrack"));
        btnResetTrack->setGeometry(QRect(540, 350, 101, 23));
        gridLayoutWidget = new QWidget(tab2);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(650, 350, 341, 139));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        btnStartTimeSetInstant = new QPushButton(gridLayoutWidget);
        btnStartTimeSetInstant->setObjectName(QStringLiteral("btnStartTimeSetInstant"));

        gridLayout->addWidget(btnStartTimeSetInstant, 3, 2, 1, 1);

        btnEndTimeSetInstant = new QPushButton(gridLayoutWidget);
        btnEndTimeSetInstant->setObjectName(QStringLiteral("btnEndTimeSetInstant"));

        gridLayout->addWidget(btnEndTimeSetInstant, 4, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        startTime = new QTimeEdit(gridLayoutWidget);
        startTime->setObjectName(QStringLiteral("startTime"));
        startTime->setCurrentSection(QDateTimeEdit::HourSection);

        gridLayout->addWidget(startTime, 3, 1, 1, 1);

        endTime = new QTimeEdit(gridLayoutWidget);
        endTime->setObjectName(QStringLiteral("endTime"));
        endTime->setCurrentSection(QDateTimeEdit::HourSection);

        gridLayout->addWidget(endTime, 4, 1, 1, 1);

        progressBar = new QProgressBar(gridLayoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setValue(0);
        progressBar->setTextVisible(true);

        gridLayout->addWidget(progressBar, 5, 0, 1, 3);

        startBtn = new QPushButton(gridLayoutWidget);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setEnabled(true);
        startBtn->setStyleSheet(QStringLiteral("color: rgb(0, 111, 81)"));

        gridLayout->addWidget(startBtn, 2, 0, 1, 1);

        pauseBtn = new QPushButton(gridLayoutWidget);
        pauseBtn->setObjectName(QStringLiteral("pauseBtn"));
        pauseBtn->setCheckable(true);

        gridLayout->addWidget(pauseBtn, 2, 1, 1, 1);

        nextBtn = new QPushButton(gridLayoutWidget);
        nextBtn->setObjectName(QStringLiteral("nextBtn"));

        gridLayout->addWidget(nextBtn, 2, 2, 1, 1);

        playerControls = new QFrame(tab2);
        playerControls->setObjectName(QStringLiteral("playerControls"));
        playerControls->setGeometry(QRect(240, 310, 401, 31));
        playerControls->setFrameShape(QFrame::StyledPanel);
        playerControls->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_2 = new QWidget(playerControls);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 401, 31));
        playerControlsLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        playerControlsLayout->setSpacing(6);
        playerControlsLayout->setContentsMargins(11, 11, 11, 11);
        playerControlsLayout->setObjectName(QStringLiteral("playerControlsLayout"));
        playerControlsLayout->setContentsMargins(0, 0, 0, 0);
        btnPlayPause = new QPushButton(horizontalLayoutWidget_2);
        btnPlayPause->setObjectName(QStringLiteral("btnPlayPause"));

        playerControlsLayout->addWidget(btnPlayPause);

        framePosSlider = new QSlider(horizontalLayoutWidget_2);
        framePosSlider->setObjectName(QStringLiteral("framePosSlider"));
        framePosSlider->setOrientation(Qt::Horizontal);

        playerControlsLayout->addWidget(framePosSlider);

        labelTime = new QLabel(horizontalLayoutWidget_2);
        labelTime->setObjectName(QStringLiteral("labelTime"));

        playerControlsLayout->addWidget(labelTime);

        adjustBox = new QFrame(tab2);
        adjustBox->setObjectName(QStringLiteral("adjustBox"));
        adjustBox->setGeometry(QRect(240, 380, 401, 61));
        adjustBox->setFrameShape(QFrame::StyledPanel);
        adjustBox->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_5 = new QWidget(adjustBox);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(0, 0, 401, 51));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(verticalLayoutWidget_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_9);

        adjustSlider = new QSlider(verticalLayoutWidget_5);
        adjustSlider->setObjectName(QStringLiteral("adjustSlider"));
        adjustSlider->setLayoutDirection(Qt::RightToLeft);
        adjustSlider->setStyleSheet(QStringLiteral("background-color: rgb(255, 85, 0);"));
        adjustSlider->setMaximum(255);
        adjustSlider->setPageStep(10);
        adjustSlider->setValue(200);
        adjustSlider->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(adjustSlider);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QStringLiteral("tab3"));
        tableView = new QTableView(tab3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 10, 411, 301));
        tabWidget->addTab(tab3, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionAbrirVideo);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionToolPolygon);
        mainToolBar->addAction(actionToolLine);
        mainToolBar->addAction(actionToolArrow);
        mainToolBar->addAction(actionToolRectangle);
        mainToolBar->addAction(actionToolCircle);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        toolBox->setCurrentIndex(3);
        btnConfirm->setDefault(false);
        btnCancel->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LaBehave", nullptr));
        actionAbrirVideo->setText(QApplication::translate("MainWindow", "Abrir V\303\255deo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionAbrirVideo->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionToolLine->setText(QApplication::translate("MainWindow", "Linha", nullptr));
        actionToolArrow->setText(QApplication::translate("MainWindow", "Flecha", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToolArrow->setToolTip(QApplication::translate("MainWindow", "Flecha", nullptr));
#endif // QT_NO_TOOLTIP
        actionToolRectangle->setText(QApplication::translate("MainWindow", "Ret\303\242ngulo", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToolRectangle->setToolTip(QApplication::translate("MainWindow", "Ret\303\242ngulo", nullptr));
#endif // QT_NO_TOOLTIP
        actionToolCircle->setText(QApplication::translate("MainWindow", "C\303\255rculo", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToolCircle->setToolTip(QApplication::translate("MainWindow", "C\303\255rculo", nullptr));
#endif // QT_NO_TOOLTIP
        actionToolPolygon->setText(QApplication::translate("MainWindow", "Pol\303\255gono", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToolPolygon->setToolTip(QApplication::translate("MainWindow", "Pol\303\255gono", nullptr));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "Projeto", nullptr));
        labelPath->setText(QApplication::translate("MainWindow", "Caminho: ", nullptr));
        configBox->setTitle(QApplication::translate("MainWindow", "Configura\303\247\303\265es", nullptr));
        checkShowPoint->setText(QApplication::translate("MainWindow", "Posi\303\247\303\243o da cobaia", nullptr));
        checkShowRect->setText(QApplication::translate("MainWindow", "Bounding box", nullptr));
        checkShowContour->setText(QApplication::translate("MainWindow", "Contorno da cobaia", nullptr));
        checkShowMovement->setText(QApplication::translate("MainWindow", "Contorno de movimento", nullptr));
        chechShowId->setText(QApplication::translate("MainWindow", "Identifica\303\247\303\243o da cobaia", nullptr));
        checkShowTrack->setText(QApplication::translate("MainWindow", "Trajet\303\263ria recente", nullptr));
        checkShowDistance->setText(QApplication::translate("MainWindow", "Dist\303\242ncia percorrida", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "Visualizar", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "amostras:", nullptr));
        btnSetBackground->setText(QApplication::translate("MainWindow", "Extrair", nullptr));
        btnSetFrameBackground->setText(QApplication::translate("MainWindow", "Extrair do instante atual", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("MainWindow", "Background", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Refer\303\252ncia m\303\251trica", nullptr));
        labelPixelsPerMeter->setText(QApplication::translate("MainWindow", "0 pixels/metro", nullptr));
        btnMeassure->setText(QApplication::translate("MainWindow", "Medir", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("MainWindow", "Op\303\247\303\265es", nullptr));
        label->setText(QApplication::translate("MainWindow", "Zona transit\303\241vel", nullptr));
        btnZoneGlobal->setText(QApplication::translate("MainWindow", "Definir", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Zonas", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Adicionar", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Remover", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Zonas ocultas", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Adicionar", nullptr));
        pushButton_5->setText(QApplication::translate("MainWindow", "Remover", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "Zonas", nullptr));
        btnAnimalSelect->setText(QApplication::translate("MainWindow", "Selecionar cobaia", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Editar", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Configura\303\247\303\265es da cobaia", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Nome:", nullptr));
        pushButton_6->setText(QApplication::translate("MainWindow", "Ok", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("MainWindow", "Cobaia", nullptr));
        checkCreateTrackMap->setText(QApplication::translate("MainWindow", "Gerar mapa do trajeto", nullptr));
        toolBox->setItemText(toolBox->indexOf(pageAnalysis), QApplication::translate("MainWindow", "An\303\241lise", nullptr));
        btnConfirm->setText(QApplication::translate("MainWindow", "Confirmar", nullptr));
        btnCancel->setText(QApplication::translate("MainWindow", "Cancelar", nullptr));
        btnResetTrack->setText(QApplication::translate("MainWindow", "Resetar trajet\303\263ria", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Final:", nullptr));
        btnStartTimeSetInstant->setText(QApplication::translate("MainWindow", "Instante atual", nullptr));
        btnEndTimeSetInstant->setText(QApplication::translate("MainWindow", "Instante atual", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "In\303\255cio:", nullptr));
        startTime->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        endTime->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        startBtn->setText(QApplication::translate("MainWindow", "Iniciar An\303\241lise", nullptr));
        pauseBtn->setText(QApplication::translate("MainWindow", "Pausar An\303\241lise", nullptr));
        nextBtn->setText(QApplication::translate("MainWindow", "Avan\303\247ar Frame >>", nullptr));
        btnPlayPause->setText(QApplication::translate("MainWindow", "Play", nullptr));
        labelTime->setText(QApplication::translate("MainWindow", "00:00:00", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Ajuste de contraste", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "An\303\241lise", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QApplication::translate("MainWindow", "Resultados", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
