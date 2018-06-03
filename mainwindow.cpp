#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.cpp"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->confirmBox->hide();
    ui->configBox->setEnabled(false);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

    ui->graphicsViewAlternative->setScene(new QGraphicsScene(this));
    ui->graphicsViewAlternative->scene()->addItem(&pixmapAlternative);

    ui->graphicsViewBackground->setScene(new QGraphicsScene(this));
    ui->graphicsViewBackground->scene()->addItem(&pixmapBackground);

    ui->slider->setMaximum(255);
    ui->slider->setValue(100);

    ui->alternativeViewSelector->addItem("máscara");
}

MainWindow::~MainWindow()
{
    delete ui;
}

Point MainWindow::getFrameCursor(QGraphicsView& graphicsView, Mat& frame){
    QPoint qp = graphicsView.mapFromGlobal(QPoint(QCursor::pos()));
    int    DX = frame.cols,
           dx = (float)graphicsView.width(),
           DY = frame.rows,
           dy = (float)graphicsView.height();
    float  pmx = (float)DX/(float)dx,
           pmy = (float)DY/(float)dy;

    if(DY>DX) pmx *= ((float)DY*(float)dx)/((float)DX*(float)dy);
    else      pmy /= ((float)DY*(float)dx)/((float)DX*(float)dy);

    Point p = Point( qp.x()*pmx + ((float)DX/2 - (float)dx*pmx/2) ,
                     qp.y()*pmy + ((float)DY/2 - (float)dy*pmy/2) );

    if      (p.x > DX) p.x = DX;
    else if (p.x <  0) p.x =  0;
    if      (p.y > DY) p.y = DY;
    else if (p.y <  0) p.y =  0;

    return p;
}

QTime MainWindow::getVideoTime(){
    QTime time(0,0,0);
    time = time.addSecs(video.get(CAP_PROP_POS_FRAMES)/video.get(CAP_PROP_FPS));
    return time;
}
QTime MainWindow::getVideoDuration(){
    QTime duration(0,0,0);
    duration = duration.addSecs(video.get(CV_CAP_PROP_FRAME_COUNT)/video.get(CV_CAP_PROP_FPS));
    return duration;
}

void MainWindow::setBackground(uint samples)
{
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>();
    Mat foregroundMask, frameCopy;

    ui->statusBar->showMessage("Extraindo background...");
    frameCopy = frame.clone();

    video.set(CAP_PROP_POS_FRAMES, 0);
    video >> frame;
    foregroundMask.create(background.size(), background.type());

    for(uint i=0; i<samples; i++){
        video.set(CAP_PROP_POS_FRAMES, (video.get(CAP_PROP_FRAME_COUNT)/samples)*i);
        video >> frame;
        bg_model->apply(frame, foregroundMask);
    }

    bg_model->getBackgroundImage(background);
    cvtColor(background, background, COLOR_BGR2RGB);
    video.set(CAP_PROP_POS_FRAMES, 0);

    QImage qimg(background.data,
                background.cols,
                background.rows,
                background.step,
                QImage::Format_RGB888);

    pixmapBackground.setPixmap( QPixmap::fromImage(qimg) );
    ui->graphicsViewBackground->fitInView(&pixmapBackground, Qt::KeepAspectRatio);

    frame = frameCopy.clone();
    ui->statusBar->showMessage("Concluído!", 5000);
}
void MainWindow::setBackground(Mat& frame){
    background = frame.clone();

    QImage qimg(background.data,
                background.cols,
                background.rows,
                background.step,
                QImage::Format_RGB888);

    pixmapBackground.setPixmap( QPixmap::fromImage(qimg) );
    ui->graphicsViewBackground->fitInView(&pixmapBackground, Qt::KeepAspectRatio);
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

    // Processo inicial --------------------------------------------------------------------------------------------
    if(!video.open(ui->videoEdit->text().trimmed().toStdString())) return;

    video >> frame;
    cvtColor(frame, frame, COLOR_BGR2RGB);

    maskZoneGlobal.create(frame.size(), CV_8UC1);
    maskZoneGlobal = Scalar::all(1);

    ui->graphicsView->setSceneRect(0, 0, frame.cols, frame.rows);
    ui->graphicsViewAlternative->setSceneRect(0, 0, frame.cols, frame.rows);
    ui->framePosSlider->setMaximum(video.get(CV_CAP_PROP_FRAME_COUNT) - 1);

    ui->startTime->setMaximumTime(getVideoDuration());
    ui->endTime->setMaximumTime(getVideoDuration());
    ui->endTime->setTime(getVideoDuration());


    ui->configBox->setEnabled(true);
    // -------------------------------------------------------------------------------------------------------------

    Mat frameCopy;
    Point p;

    while(video.isOpened() && !lock){

        if(ui->graphicsView->underMouse())
            QApplication::setOverrideCursor(Qt::BlankCursor);
        else QApplication::setOverrideCursor(Qt::ArrowCursor);
        p = getFrameCursor(*ui->graphicsView, frame);

        if(!pause){
            video >> frame;
            cvtColor(frame, frame, COLOR_BGR2RGB);
        }

        if(!frame.empty())
        {

            // Selecao se pausado -------------------------------------------------
            if(pause){
                frameCopy = frame.clone();

                if(QApplication::mouseButtons() == Qt::LeftButton
                && (tool != -1)
                && (tool != TOOL_POLYGON)
                && (p.x > 0)
                && (p.x < frame.cols)
                && (p.y > 0)
                && (p.y < frame.rows) ){
                    if(!flagSelectPoints){
                        selectPoints[0] = getFrameCursor(*ui->graphicsView, frame);
                        selectPoints[1] = getFrameCursor(*ui->graphicsView, frame);
                        flagSelectPoints = true;
                    }else{
                        selectPoints[1] = getFrameCursor(*ui->graphicsView, frame);
                    }
                }else flagSelectPoints = false;

                if(norm(selectPoints[0]-selectPoints[1]) > 0){

                    //linha
                    if(tool == TOOL_LINE)
                        line(frame, selectPoints[0], selectPoints[1], CV_RGB(0,0,255), 3);

                    //flecha
                    if(tool == TOOL_ARROW)
                        arrowedLine(frame, selectPoints[0], selectPoints[1], CV_RGB(0,0,255), 3);

                    //retangulo
                    if(tool == TOOL_RECTANGLE)
                        rectangle(frame, selectPoints[0], selectPoints[1], CV_RGB(0,255,0), 3);

                    //circulo
                    if(tool == TOOL_CIRCLE)
                        circle(frame, (selectPoints[0]+selectPoints[1])*.5, norm(selectPoints[0]-selectPoints[1])/2, CV_RGB(255,0,0), 3);
                }

                //poligono
                if(tool == TOOL_POLYGON){
                    if(QApplication::mouseButtons() == Qt::LeftButton){
                        if(!flagSelectPolygon
                        && (p.x > 0)
                        && (p.x < frame.cols)
                        && (p.y > 0)
                        && (p.y < frame.rows) )
                        {
                            selectPolygon.push_back( getFrameCursor(*ui->graphicsView, frame) );
                            flagSelectPolygon = true;
                        }
                    }   else flagSelectPolygon = false;

                    if(QApplication::mouseButtons() == Qt::RightButton){
                        if(!flagSelectPolygon2 && !selectPolygon.empty()){
                            selectPolygon.pop_back();
                            flagSelectPolygon2 = true;
                        }
                    }else   flagSelectPolygon2 = false;

                    polylines(frame, selectPolygon, true, CV_RGB(0,255,0), 3);
                }   else selectPolygon.clear();


                if(!ui->btnConfirm->isDown() && mode !=0){
                    if( ((norm(selectPoints[0]-selectPoints[1]) > 0) || (!selectPolygon.empty())) )
                    {
                        // MEDIDA -----------------------------------------------------------------
                        if(mode == MODE_MEASSURE && QApplication::mouseButtons() == Qt::LeftButton){
                            putText(frame,
                                    to_string((int)norm(selectPoints[0]-selectPoints[1])) + "px",
                                    getFrameCursor(*ui->graphicsView, frame),
                                    FONT_HERSHEY_PLAIN,
                                    2, CV_RGB(255,255,0), 2);
                        }

                        // ZONA GLOBAL ------------------------------------------------------------
                        if(mode == MODE_ZONE_GLOBAL){
                            maskZoneGlobal = Scalar::all(0);
                            Mat frameMasked;

                            if(tool == TOOL_RECTANGLE)
                                maskZoneGlobal(Rect(selectPoints[0], selectPoints[1])).setTo(Scalar(255));
                            if(tool == TOOL_CIRCLE)
                                circle(maskZoneGlobal,
                                      (selectPoints[0]+selectPoints[1])*.5,
                                       norm(selectPoints[0]-selectPoints[1])/2,
                                       Scalar(255),
                                       CV_FILLED);
                            if(tool == TOOL_POLYGON)
                                fillConvexPoly( maskZoneGlobal, selectPolygon, Scalar(1) );

                            frame.copyTo(frameMasked, maskZoneGlobal);
                            addWeighted(frame, 0.5, frameMasked, 0.5, 0, frame);
                        }
                    }
                }


            }// -----------------------------------------------------------------------------------


            // Indicador de tempo
            ui->labelTime->setText(getVideoTime().toString());

            // slider para ajustar o frame atual
            if(QApplication::mouseButtons() != Qt::LeftButton)
                ui->framePosSlider->setValue(video.get(CV_CAP_PROP_POS_FRAMES));

            // Mostra o frame -----------------
            if(pause) circle(frame, p, 3, CV_RGB(0,140,255), 2);

            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);

            pixmap.setPixmap( QPixmap::fromImage(qimg) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);

            if(pause) frame = frameCopy.clone();
            // --------------------------------

            // video chega no final
            if(video.get(CV_CAP_PROP_POS_FRAMES) == video.get(CV_CAP_PROP_FRAME_COUNT)){
                pause = true;
                ui->btnPlayPause->setText("Play");
                video.set(CV_CAP_PROP_POS_FRAMES, 0);
            }

        }   qApp->processEvents();
    }
}

void MainWindow::on_startBtn_pressed()
{
    if(video.isOpened() && lock){
        ui->startBtn->setText("Reiniciar Análise");
        ui->playerControls->setEnabled(true);
        video.release();
        lock = false;
        return;
    }
    if(background.empty()){
        ui->statusBar->showMessage("Defina o background primeiro!");
        return;
    }

    video.open(ui->videoEdit->text().trimmed().toStdString());

    // frames de inicio e termino -------------------------
    uint startTimeSecs = ui->startTime->time().hour()   * 3600 +
                         ui->startTime->time().minute() * 60 +
                         ui->startTime->time().second();
    uint endTimeSecs =   ui->endTime->time().hour()   * 3600 +
                         ui->endTime->time().minute() * 60 +
                         ui->endTime->time().second();

    startFrame = startTimeSecs * video.get(CV_CAP_PROP_FPS);
    endFrame = endTimeSecs     * video.get(CV_CAP_PROP_FPS);

    video.set(CV_CAP_PROP_POS_FRAMES, startFrame);
    // ----------------------------------------------------

    // Gerar ----------------------------------------------
    if(ui->checkCreateTrackMap->isChecked())
        ui->alternativeViewSelector->addItem("trajeto");
    // ----------------------------------------------------

    ui->startBtn->setText("Parar");
    ui->playerControls->setEnabled(false);
    ui->pageAnalysis->setEnabled(false);
    ui->progressBar->setMinimum(startFrame);
    ui->progressBar->setMaximum(endFrame);
    trackImg.create(frame.size(), frame.type());
    trackImg = Scalar::all(0);
    lock = true;

    // Variaveis ------------
    Mat frame2;
    vector<vector<Point>> contours, contours_poly;
    vector<Vec4i> hierarchy;
    vector<Rect> boundRect;
    vector<Moments> mu;                // moments
    vector<Point2f> mc;                // centro
    vector<Point> pts, trackPath;      // trajeto;
    uchar value;
    vector<int> area;
    int avArea, avAreaSum = 0;
    int gtIndexContour = 0;
    const int margin = 15, learnSizeCount = 200;

    //           Cores:
    const Scalar red   = Scalar(255, 0, 0),
                 cyan  = Scalar(0, 255, 255);
    // ----------------------

    while(video.isOpened())
    {
        video >> frame;
        value = ui->slider->value();
        ui->progressBar->setValue(video.get(CV_CAP_PROP_POS_FRAMES));

        if(!frame.empty())
        {
            frame.copyTo(frame2, maskZoneGlobal);

            // frame2 - background
            subtract(frame2, background, frame2);

            // Conversao de cores
            cvtColor(frame2, frame2, COLOR_BGR2GRAY);
            cvtColor(frame, frame, COLOR_BGR2RGB);

            // Aplica o threshold
            threshold(frame2, frame2, value, 255, THRESH_BINARY);
            blur(frame2, frame2, Size(3, 3));

            // transformacao do frame (verificar melhor depois)
            Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5,5));
            morphologyEx(frame2, frame2, CV_MOP_OPEN, element);

            // Encontra e desenha os contornos ------------------------------------------------------------------------
            findContours(frame2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
            contours_poly = vector<vector<Point>>(contours.size());
            boundRect = vector<Rect>(contours.size());
            mu = vector<Moments>(contours.size());
            mc = vector<Point2f>(contours.size());

            // organiza os contornos por maior area
            sortContours(contours);

            for(uint i=0; i<contours.size(); i++){
                approxPolyDP( contours[i], contours_poly[i], 0.005 * arcLength(contours[i], true), true );
                boundRect[i] = boundingRect( Mat(contours_poly[i]) );
                mu[i] = moments(contours_poly[i], false);
                mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
            }


            if(contours.size() > 0)
            {
                // anti-teleporte -------------------------------------------------------------------------------------
                // TODO: tratar eventos antes do programa atingir learnCount
                gtIndexContour = 0;

                if(pts.size() == learnSizeCount)
                {
                    pts.erase(pts.begin());
                    avAreaSum -= area[0];
                    area.erase(area.begin());

                    for(uint i=0; i<mc.size(); i++){
                        if(norm(Point(mc[i]) - pts[pts.size()-1]) < norm(Point(mc[gtIndexContour]) - pts[pts.size()-1]))
                            if(abs(contourArea(contours_poly[i]) - avArea) < avArea*0.35) // diferenca de area
                                if(norm(pts[pts.size()-1] - Point(mc[i])) < 7)            // distancia entre pontos
                                    gtIndexContour = i;
                    }
                }

                // calcula a area media da cobaia
                int currentArea = contourArea(contours[gtIndexContour]);
                area.push_back(currentArea);
                avAreaSum += currentArea;
                avArea = avAreaSum / area.size();

                ui->statusBar->showMessage("av:" + QString::number(avArea)
                                         + " atual:" + QString::number(currentArea)
                                         + " diferenca:" + QString::number(abs(contourArea(contours_poly[gtIndexContour]) - avArea)));

                if(pts.empty())
                    pts.push_back(mc[gtIndexContour]);
                else if(Point(mc[gtIndexContour]) != pts[pts.size()-1])
                    pts.push_back(mc[gtIndexContour]);

                // ----------------------------------------------------------------------------------------------------

                //trajeto
                if(ui->checkCreateTrackMap->isChecked() && pts.size() > 1){
                    uint trackColor = (((video.get(CV_CAP_PROP_POS_FRAMES) - startFrame)*255)/endFrame);
                    line(trackImg, pts[pts.size()-2], pts[pts.size()-1], Scalar(trackColor,0,255-trackColor), 2);
                }
                if(ui->checkShowTrack->isChecked())
                    polylines(frame, pts, false, red, 2);

                //contorno:
                if(ui->checkShowContour->isChecked())
                    drawContours(frame, contours_poly, gtIndexContour, CV_RGB(0,140,255), 2, 8, hierarchy, 0, Point());

                //retangulo:
                if(ui->checkShowRect->isChecked()){
                    rectangle(frame, Point(boundRect[gtIndexContour].tl().x - margin, boundRect[gtIndexContour].tl().y - margin),
                                     Point(boundRect[gtIndexContour].br().x + margin, boundRect[gtIndexContour].br().y + margin),
                                     cyan, 2, 8, 0);
                }

                //centro
                if(ui->checkShowPoint->isChecked())
                    circle(frame, mc[gtIndexContour], 5, red, -1, 8, 0);


                //TEXTO:
                string text = "";

                //identificacao da cobaia
                if(ui->chechShowId->isChecked())
                    text += "Rato : ";

                //distancia percorrida
                trackPath.push_back(pts[pts.size()-1]);
                if(ui->checkShowDistance->isChecked())
                    text += to_string(arcLength(trackPath, false)/pixelsPerMeter) + " m";

                putText(frame,
                        text ,
                        Point(boundRect[gtIndexContour].tl().x - margin, boundRect[gtIndexContour].tl().y - margin - 5),
                        FONT_HERSHEY_PLAIN, 1.5, CV_RGB(0,140,255), 2);
            }

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

            if(ui->alternativeViewSelector->currentText() == "máscara") frameAlternative = &frame2;
            if(ui->alternativeViewSelector->currentText() == "trajeto") frameAlternative = &trackImg;

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

            // Fim da analise
            if(video.get(CV_CAP_PROP_POS_FRAMES) == endFrame){
                video.release();
                ui->startBtn->setText("Reiniciar Análise");
            }

            // reseta a trajetoria
            if(ui->btnResetTrack->isDown()){
                pts.clear();
            }
        }
        qApp->processEvents();
}
}

// Impede o programa de fechar caso o video ainda esteja em execucao
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(video.isOpened() && lock){
        QMessageBox::warning(this, "Atenção", "Pare a análise antes de fechar o programa!");
        event->ignore();
    }else{
        video.release();
        event->accept();
    }
}

void MainWindow::on_btnPlayPause_pressed()
{
    pause = !pause;
    if(pause) ui->btnPlayPause->setText("Play");
    else      ui->btnPlayPause->setText("Pause");
}

void MainWindow::on_framePosSlider_sliderReleased()
{
    if(video.isOpened()){
        video.set(CV_CAP_PROP_POS_FRAMES, ui->framePosSlider->value());
        video >> frame;
        cvtColor(frame, frame, COLOR_BGR2RGB);
    }
}

void MainWindow::on_actionToolLine_triggered()
{
    tool = TOOL_LINE;

    selectPoints[0] = selectPoints[1] = Point(0,0);
    selectPolygon.clear();

    ui->actionToolLine->setChecked(true);
    ui->actionToolArrow->setChecked(false);
    ui->actionToolRectangle->setChecked(false);
    ui->actionToolCircle->setChecked(false);
    ui->actionToolPolygon->setChecked(false);
}
void MainWindow::on_actionToolArrow_triggered()
{
    tool = TOOL_ARROW;

    selectPoints[0] = selectPoints[1] = Point(0,0);
    selectPolygon.clear();

    ui->actionToolArrow->setChecked(true);
    ui->actionToolLine->setChecked(false);
    ui->actionToolRectangle->setChecked(false);
    ui->actionToolCircle->setChecked(false);
    ui->actionToolPolygon->setChecked(false);
}
void MainWindow::on_actionToolRectangle_triggered()
{
    tool = TOOL_RECTANGLE;

    selectPoints[0] = selectPoints[1] = Point(0,0);
    selectPolygon.clear();

    ui->actionToolRectangle->setChecked(true);
    ui->actionToolArrow->setChecked(false);
    ui->actionToolLine->setChecked(false);
    ui->actionToolCircle->setChecked(false);
    ui->actionToolPolygon->setChecked(false);
}
void MainWindow::on_actionToolCircle_triggered()
{
    tool = TOOL_CIRCLE;

    selectPoints[0] = selectPoints[1] = Point(0,0);
    selectPolygon.clear();

    ui->actionToolCircle->setChecked(true);
    ui->actionToolArrow->setChecked(false);
    ui->actionToolRectangle->setChecked(false);
    ui->actionToolLine->setChecked(false);
    ui->actionToolPolygon->setChecked(false);
}
void MainWindow::on_actionToolPolygon_triggered()
{
    tool = TOOL_POLYGON;

    selectPoints[0] = selectPoints[1] = Point(0,0);
    selectPolygon.clear();

    ui->actionToolPolygon->setChecked(true);
    ui->actionToolArrow->setChecked(false);
    ui->actionToolRectangle->setChecked(false);
    ui->actionToolLine->setChecked(false);
    ui->actionToolCircle->setChecked(false);
}

void MainWindow::on_btnConfirm_pressed()
{
    if( (norm(selectPoints[0] - selectPoints[1]) == 0) && (selectPolygon.size() < 3) ){
        ui->statusBar->showMessage("Selecione uma área!", 5000);
        return;
    }

    if(mode == MODE_MEASSURE){
        pixelsPerMeter =  norm(selectPoints[0] - selectPoints[1]) /
                          QInputDialog::getDouble(this, "Medida", "Valor em metros:", 0.0, 0, 999, 3);
        ui->labelPixelsPerMeter->setText(QString::number(pixelsPerMeter, ' ', 2) + " pixels/metro");

        ui->checkShowDistance->setEnabled(true);
    }

    if(mode == MODE_ZONE_GLOBAL){
        if(tool == TOOL_POLYGON){
            zoneGlobal.type = SHAPE_POLYGON;
            zoneGlobal.points = selectPolygon;
        }else{
            if(tool == TOOL_RECTANGLE) zoneGlobal.type = SHAPE_RECTANGLE;
            if(tool == TOOL_CIRCLE)    zoneGlobal.type = SHAPE_CIRCLE;

            zoneGlobal.points.push_back(selectPoints[0]);
            zoneGlobal.points.push_back(selectPoints[1]);
        }
    }

    ui->actionAbrirVideo->setEnabled(true);
    ui->actionToolCircle->setEnabled(true);
    ui->actionToolLine->setEnabled(true);
    ui->actionToolArrow->setEnabled(true);
    ui->actionToolPolygon->setEnabled(true);
    ui->actionToolRectangle->setEnabled(true);

    selectPoints[0] = selectPoints[1] = Point(0,0);
    selectPolygon.clear();

    ui->confirmBox->hide();
    mode = 0;
}
void MainWindow::on_btnCancel_pressed()
{
    ui->actionAbrirVideo->setEnabled(true);
    ui->actionToolCircle->setEnabled(true);
    ui->actionToolLine->setEnabled(true);
    ui->actionToolArrow->setEnabled(true);
    ui->actionToolPolygon->setEnabled(true);
    ui->actionToolRectangle->setEnabled(true);

    selectPoints[0] = selectPoints[1] = Point(0,0);
    ui->confirmBox->hide();
    mode = 0;
}

void MainWindow::on_btnMeassure_pressed()
{
    ui->actionToolArrow->trigger();
    ui->confirmBox->show();
    ui->actionAbrirVideo->setEnabled(false);
    ui->actionToolCircle->setEnabled(false);
    ui->actionToolLine->setEnabled(false);
    ui->actionToolPolygon->setEnabled(false);
    ui->actionToolRectangle->setEnabled(false);

    mode = MODE_MEASSURE;
}

void MainWindow::on_btnZoneGlobal_pressed()
{
    ui->actionToolRectangle->trigger();
    ui->confirmBox->show();
    ui->actionAbrirVideo->setEnabled(false);
    ui->actionToolLine->setEnabled(false);
    ui->actionToolArrow->setEnabled(false);

    mode = MODE_ZONE_GLOBAL;
}

void MainWindow::on_btnSetBackground_pressed()
{
    setBackground(ui->nSamples->value());
}
void MainWindow::on_btnSetFrameBackground_pressed()
{
    setBackground(frame);
}

void MainWindow::on_btnStartTimeSetInstant_pressed()
{
    ui->startTime->setTime(getVideoTime());
}
void MainWindow::on_btnEndTimeSetInstant_pressed()
{
    ui->endTime->setTime(getVideoTime());
}
