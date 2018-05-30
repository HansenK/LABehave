#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.cpp"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

    ui->graphicsViewAlternative->setScene(new QGraphicsScene(this));
    ui->graphicsViewAlternative->scene()->addItem(&pixmapAlternative);

    ui->slider->setMaximum(255);
    ui->slider->setValue(100);

    ui->alternativeViewSelector->addItem("background");
    ui->alternativeViewSelector->addItem("trajetória");
    ui->alternativeViewSelector->addItem("contornos");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbrirVideo_triggered()
{
    QString videoFileName = QFileDialog::getOpenFileName(
                this,
                tr("Abrir Arquivo"),
                "C://",
                "Videos (*.mp4 *.avi *.mov *.wmv)"
                );

    ui->videoEdit->setText(videoFileName);
}


void MainWindow::on_startBtn_pressed()
{
    if(video.isOpened()){
        ui->startBtn->setText("Start");
        video.release();
        return;
    }

    bool isCamera;
    int cameraIndex = ui->videoEdit->text().toInt(&isCamera);

    if(isCamera){
        if(!video.open(cameraIndex)){
            QMessageBox::critical(this,
            "Camera Error",
            "Make sure you entered a correct camera index,"
            "<br>or that the camera is not being accessed by another program!");
            return;
        }
    }else{
        if(!video.open(ui->videoEdit->text().trimmed().toStdString())){
            QMessageBox::critical(this,
            "Video Error",
            "Make sure you entered a correct and supported video file path,"
            "<br>or a correct RTSP feed URL!");
            return;
        }
    }

    ui->startBtn->setText("Parar");

    // Variaveis ------------
    Mat frame, frame2, background, trackImg;
    vector<vector<Point>> contours, contours_poly, hull;
    vector<Vec4i> hierarchy;
    vector<Rect> boundRect;
    vector<Moments> mu; // moments
    vector<Point2f> mc; // centro
    vector<Point> pts;  // trajeto
    Point *path;        // ''
    int npts;           // ''
    uchar value;

    //           Cores:
    const Scalar red   = Scalar(255, 0, 0),
                 green = Scalar(0, 255, 0),
                 cyan  = Scalar(0, 255, 255);

    int margin = 15, gtArea, gtIndexContour = 0;
    // ----------------------

    // Gera o background -------------------------------------------------------------------------------------------
    ui->statusBar->showMessage("Gerando background...");
    getBackground(video, background, 30);
    cvtColor(background, background, COLOR_BGR2RGB);
    trackImg = background.clone();
    // -------------------------------------------------------------------------------------------------------------

    while(video.isOpened())
    {
        video >> frame;
        frame2 = frame.clone();
        value = ui->slider->value();

        if(!frame.empty())
        {
            // frame2 - background
            subtract(frame2, background, frame2);

            // Conversao de cores
            cvtColor(frame2, frame2, COLOR_BGR2GRAY);
            cvtColor(frame, frame, COLOR_BGR2RGB);

            // Aplica o efeifo Canny
            threshold(frame2, frame2, value, 255, THRESH_BINARY);
            Canny(frame2, frame2, 100, 255);
            blur(frame2, frame2, Size(3, 3));


            // Encontra e desenha os contornos ------------------------------------------------------------------------
            findContours(frame2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
            contours_poly = hull = vector<vector<Point>>(contours.size());
            boundRect = vector<Rect>(contours.size());
            mu = vector<Moments>(contours.size());
            mc = vector<Point2f>(contours.size());
            gtArea = 0;

            for(uint i=0; i<contours.size(); i++){
                approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
                boundRect[i] = boundingRect( Mat(contours_poly[i]) );

                // Encontra o contorno com maior area
                if(contourArea(contours_poly[i]) > gtArea){
                    gtArea = contourArea(contours_poly[i]);
                    gtIndexContour = i;
                }

                convexHull( Mat(contours[i]), hull[i] );
                mu[i] = moments(contours[i], false);
                mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
            }


            if(contours.size() > 0){

                //contorno: (crash)
                //drawContours(frame, contours_poly, gtIndexContour, green, 3, 8, hierarchy, 0, Point());

                //hull: (crash)
                //drawContours(frame, hull, gtIndexContour, red, 2, 8, vector<Vec4i>(), 0, Point());

                //retangulo:
                rectangle(frame, Point(boundRect[gtIndexContour].tl().x - margin, boundRect[gtIndexContour].tl().y - margin),
                                 Point(boundRect[gtIndexContour].br().x + margin, boundRect[gtIndexContour].br().y + margin),
                                 cyan, 2, 8, 0);

                //centro
                circle(frame, mc[gtIndexContour], 5, red, -1, 8, 0);

                //trajeto
                pts.push_back(mc[gtIndexContour]);
                path = (Point*) Mat(pts).data;
                npts = Mat(pts).rows;
                polylines(trackImg, &path, &npts, 1, false, green, 2);

                //texto:
                putText(frame,
                        "Rato",
                        Point(boundRect[gtIndexContour].tl().x - margin, boundRect[gtIndexContour].tl().y - margin - 5),
                        FONT_HERSHEY_PLAIN, 2, cyan, 2);
            }
            // --------------------------------------------------------------------------------------------------------

            // Mostra o frame -----------------------------------------------------------
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);

            pixmap.setPixmap( QPixmap::fromImage(qimg) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);

            // Mostra a view alternativa --------------------------------------------------------------------
            Mat *frameAlternative;

            if(ui->alternativeViewSelector->currentText() == "background") frameAlternative = &background;
            if(ui->alternativeViewSelector->currentText() == "trajetória") frameAlternative = &trackImg;
            if(ui->alternativeViewSelector->currentText() == "contornos") frameAlternative = &frame2;

            QImage::Format formatAlternative = (frameAlternative->channels() == 1) ? QImage::Format_Grayscale8 :
                                               (frameAlternative->channels() == 3) ? QImage::Format_RGB888 :
                                                                                    QImage::Format_RGBA8888;
            QImage qimgAlternative(frameAlternative->data,
                                   frameAlternative->cols,
                                   frameAlternative->rows,
                                   frameAlternative->step,
                                   formatAlternative);
            pixmapAlternative.setPixmap( QPixmap::fromImage(qimgAlternative) );
            ui->graphicsViewAlternative->fitInView(&pixmap, Qt::KeepAspectRatio);
            // -----------------------------------------------------------------------------------------------

            // reseta a trajetoria
            if(ui->btnResetTrack->isDown()){
                pts.clear();
                trackImg = background.clone();
            }
        }
        qApp->processEvents();

        ui->statusBar->showMessage("Tempo: " +
                                   QString::number(video.get(CAP_PROP_POS_FRAMES)/
                                                   video.get(CAP_PROP_FPS)) + "s" );

    }

    ui->startBtn->setText("Iniciar");
}


// Impede o programa de fechar caso o video ainda esteja em execucao
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(video.isOpened()){
        QMessageBox::warning(this, "Atenção", "Pare o vídeo antes de fechar o programa!");
        event->ignore();
    }else{
        event->accept();
    }
}
