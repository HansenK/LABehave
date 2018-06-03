#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MODE_DEFAULT     0
#define MODE_MEASSURE    1
#define MODE_ZONE_GLOBAL 2

#define SHAPE_RECTANGLE 0
#define SHAPE_CIRCLE    1
#define SHAPE_POLYGON   2

#define TOOL_LINE       0
#define TOOL_ARROW      1
#define TOOL_RECTANGLE  2
#define TOOL_CIRCLE     3
#define TOOL_POLYGON    4

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include "opencv2/opencv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();

    explicit MainWindow(QWidget *parent = 0);
    cv::Point getFrameCursor(QGraphicsView& graphicsView, cv::Mat& frame);
    QTime getVideoTime();
    QTime getVideoDuration();
    void setBackground(uint samples = 15);
    void setBackground(cv::Mat& frame);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_startBtn_pressed();

    void on_actionAbrirVideo_triggered();

    void on_btnPlayPause_pressed();

    void on_framePosSlider_sliderReleased();

    void on_actionToolLine_triggered();

    void on_actionToolArrow_triggered();

    void on_actionToolRectangle_triggered();

    void on_actionToolCircle_triggered();

    void on_actionToolPolygon_triggered();

    void on_btnMeassure_pressed();

    void on_btnConfirm_pressed();

    void on_btnCancel_pressed();

    void on_btnZoneGlobal_pressed();

    void on_btnSetBackground_pressed();

    void on_btnSetFrameBackground_pressed();

    void on_btnStartTimeSetInstant_pressed();

    void on_btnEndTimeSetInstant_pressed();

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem pixmap, pixmapAlternative, pixmapBackground;
    cv::VideoCapture video;
    cv::Mat frame, background, maskZoneGlobal, trackImg;
    bool pause = 1;
    bool lock = 0;

    cv::Point selectPoints[2] = {cv::Point(0,0), cv::Point(0,0)};
    std::vector<cv::Point> selectPolygon;
    bool flagSelectPoints = false;
    bool flagSelectPolygon = false, flagSelectPolygon2 = false;
    float pixelsPerMeter = 0;

    struct zoneGlobal{
        uint type;
        std::vector<cv::Point> points;
    }zoneGlobal;

    int mode = 0;
    int tool = -1;

    int startFrame, endFrame;
};

#endif // MAINWINDOW_H
