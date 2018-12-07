#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MODE_DEFAULT       0
#define MODE_MEASSURE      1
#define MODE_ZONE_GLOBAL   2
#define MODE_ZONE_ADD      3
#define MODE_ANIMAL_SELECT 4
#define MODE_ANIMAL_EDIT   5

#define SHAPE_RECTANGLE 0
#define SHAPE_CIRCLE    1
#define SHAPE_POLYGON   2

#define TOOL_LINE       0
#define TOOL_ARROW      1
#define TOOL_RECTANGLE  2
#define TOOL_CIRCLE     3
#define TOOL_POLYGON    4

#define EV_ZONE_ENTRY     1
#define EV_ZONE_EXIT      2
#define EV_ZONE_TIME_IN   3
#define EV_ZONE_TIME_OUT  4
#define EV_IMOB_TIME      5
#define EV_DIST           6
#define EV_VEL            7


#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidget>

#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <bitset>

#include "opencv2/opencv.hpp"
#include "databasemanager.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    cv::Point getFrameCursor(QGraphicsView& graphicsView, cv::Mat& frame);
    QTime getVideoTime();
    QTime getVideoDuration();
    void setBackground(uint samples = 15);
    void setBackground(cv::Mat& frame);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionNewProject_triggered();

    void on_btnNewProject_pressed();

    bool on_actionOpenProject_triggered();

    void on_btnLoadProject_pressed();

    void on_actionOpenVideo_triggered();

    void config();

    void on_btnPlayPause_toggled(bool checked);

    void on_framePosSlider_sliderReleased();

    void on_btnSetBackground_pressed();

    void on_btnSetFrameBackground_pressed();

    void on_btnStartTimeSetInstant_pressed();

    void on_btnEndTimeSetInstant_pressed();

    void on_btnAnimalSelect_pressed();

    void on_btnConfirm_pressed();

    void on_btnCancel_pressed();

    void on_actionToolRectangle_triggered();

    void on_actionToolCircle_triggered();

    void on_actionToolPolygon_triggered();

    void on_startBtn_pressed();

    void on_btnMeassure_pressed();

    void on_actionToolArrow_triggered();

    void on_btnZoneAdd_pressed();

    void openProject(QString projectFileName);

    void on_recentProjects_itemDoubleClicked(QListWidgetItem *item);

    void on_btnZoneRemove_pressed();

    void on_actionFinish_triggered();

    void on_btnAddVideo_pressed();

    void on_btnConfig_pressed();

    void on_videoList_itemClicked();

    void on_videoList_itemDoubleClicked();

    void on_subEventSelect_currentIndexChanged(const QString &arg1);

    void on_btnAddSubEvent_pressed();

    void on_btnNewEvent_pressed();

    void on_eventResultSelect_currentIndexChanged(int index);

    void postRequest();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;

    //networking
    QNetworkAccessManager * manager;
    QNetworkRequest request;

    // projeto
    QString projectName;
    QDir projectDir;


    QGraphicsPixmapItem pixmap, pixmapPlayer, pixmapBackground;
    cv::VideoCapture video;
    std::vector<QString> videoFiles;
    cv::Mat frame, background, maskZoneGlobal, trackImg, animal, heatmap;
    bool pause = 1;
    bool lock = 0;

    cv::Point selectPoints[2] = {cv::Point(0,0), cv::Point(0,0)};
    std::vector<cv::Point> selectPolygon, animalContour;
    bool flagSelectPoints = false;
    bool flagSelectPolygon = false, flagSelectPolygon2 = false;
    double pixelsPerMeter = 0;

    // eventos --------------------------------
    struct subevent{
        int type;
        int intParam;
        float floatParam;
        string stringParam;
    };

    struct event{
        QString name;                           // nome do evento
        int subEventsCount;                     // contador de subeventos do evento
        bool allowBetween;                      // permite outros subeventos
        vector<struct subevent> subevents; // sequencia de subeventos
        vector<double> t_start;                  // tempo de inicio do evento
        vector<double> t_stop;                   // tempo de termino do evento
    };

    std::vector<struct event> events;

    // zonas ----------------------------------
    struct zone{
        uint type;
        std::vector<cv::Point> points;
        cv::Mat zoneMat;
        bool inZone;
        int nEntry;
        int nExit;
        float lastEntryTime;
        float permTime;
    };
    std::vector<struct zone> zones;
    struct zone zoneGlobal; // zona de analise
    // ----------------------------------------

    int mode = 0;
    int tool = -1;

    int startFrame, endFrame;

    // banco de dados
    DatabaseManager db;

};

#endif // MAINWINDOW_H
