#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.cpp"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->confirmBox->hide();
    ui->adjustBox->hide();
    ui->configBox->setEnabled(false);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

    ui->graphicsViewAlternative->setScene(new QGraphicsScene(this));
    ui->graphicsViewAlternative->scene()->addItem(&pixmapAlternative);

    ui->graphicsViewBackground->setScene(new QGraphicsScene(this));
    ui->graphicsViewBackground->scene()->addItem(&pixmapBackground);

    ui->slider->setMaximum(255);

    ui->alternativeViewSelector->addItem("máscara");
    ui->alternativeViewSelector->addItem("movimento");
    ui->alternativeViewSelector->addItem("orientação");
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
    duration = duration.addSecs(video.get(CAP_PROP_FRAME_COUNT)/video.get(CAP_PROP_FPS));
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
int MainWindow::setThreshold(){
    video.set(CAP_PROP_POS_FRAMES, (video.get(CAP_PROP_FRAME_COUNT)/2));
    video >> frame;
    cvtColor(frame, frame, COLOR_BGR2RGB);

    Mat frame2;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    int gtArea = 0, th;

    for(int i=1; i<255; i++){
        frame2 = frame.clone();
        frame2 = frame2 - background;
        cvtColor(frame2, frame2, COLOR_BGR2GRAY);
        threshold(frame2, frame2, i, 255, THRESH_BINARY);

        findContours(frame2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

        if(contours.size() <= 10){
            sortContours(contours);
            if(contourArea(contours[0]) > gtArea){
                gtArea = contourArea(contours[0]);
                th = i;
            }
        }
    }

    return th;
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
    ui->framePosSlider->setMaximum(video.get(CAP_PROP_FRAME_COUNT) - 1);

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

                        // SELECAO ----------------------------------------------------------------
                        if(mode == MODE_ZONE_GLOBAL || mode == MODE_ANIMAL_SELECT){
                            Mat maskSelection(frame.size(), CV_8UC1);
                            maskSelection = Scalar::all(0);
                            Mat frameMasked;

                            if(tool == TOOL_RECTANGLE)
                                maskSelection(Rect(selectPoints[0], selectPoints[1])).setTo(Scalar(255));
                            if(tool == TOOL_CIRCLE)
                                circle(maskSelection,
                                      (selectPoints[0]+selectPoints[1])*.5,
                                       norm(selectPoints[0]-selectPoints[1])/2,
                                       Scalar(255),
                                       FILLED);
                            if(tool == TOOL_POLYGON)
                                fillConvexPoly( maskSelection, selectPolygon, Scalar(1) );

                            frame.copyTo(frameMasked, maskSelection);
                            addWeighted(frame, 0.5, frameMasked, 0.5, 0, frame);

                            if(mode == MODE_ZONE_GLOBAL) maskZoneGlobal = maskSelection.clone();
                        }

                    }
                }


            }// -----------------------------------------------------------------------------------


            // Indicador de tempo
            ui->labelTime->setText(getVideoTime().toString());

            // slider para ajustar o frame atual
            if(QApplication::mouseButtons() != Qt::LeftButton)
                ui->framePosSlider->setValue(video.get(CAP_PROP_POS_FRAMES));

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

            // CONFIGURACAO DA COBAIA -------------------------------------------------
            while(mode == MODE_ANIMAL_EDIT){
                Mat animal2, animalMask;
                vector<vector<Point>> animalContours;
                vector<Vec4i> animalHierarchy;
                frame(Rect(selectPoints[0], selectPoints[1])).copyTo(animal);
                animalMask.create(animal.size(), CV_8UC1);

                if(!background.empty()){
                    subtract(animal, background((Rect(selectPoints[0], selectPoints[1]))), animalMask);
                    cvtColor(animalMask, animalMask, COLOR_RGB2GRAY);
                    threshold(animalMask, animalMask, ui->adjustSlider->value(), 255, THRESH_BINARY);
                    GaussianBlur(animalMask, animalMask, Size(3,3), 0, 0);
                }

                animal.copyTo(animal2);
                animal = Scalar::all(0);
                animal2.copyTo(animal, animalMask);

                // desenha os contornos
                findContours(animalMask, animalContours, animalHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
                if(!animalContours.empty()){
                    sortContours(animalContours); // ordena os contornos por area

                    approxPolyDP( animalContours[0], animalContour, 0.005 * arcLength(animalContours[0], true), true );
                    animalContours[0] = animalContour;

                    drawContours(animal, animalContours, 0, CV_RGB(0,140,255), 1, 8, animalHierarchy, 0, Point());
                }

                QImage qimg(animal.data,
                            animal.cols,
                            animal.rows,
                            animal.step,
                            QImage::Format_RGB888);

                pixmap.setPixmap( QPixmap::fromImage(qimg) );
                ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
                qApp->processEvents();
            }// -----------------------------------------------------------------------


            // video chega no final
            if(video.get(CAP_PROP_POS_FRAMES) == video.get(CAP_PROP_FRAME_COUNT)){
                pause = true;
                ui->btnPlayPause->setText("Play");
                video.set(CAP_PROP_POS_FRAMES, 0);
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
    if(background.empty() || animalContour.empty()){
        ui->statusBar->showMessage("Defina o background e a cobaia primeiro!");
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

    startFrame = startTimeSecs * video.get(CAP_PROP_FPS);
    endFrame = endTimeSecs     * video.get(CAP_PROP_FPS);

    video.set(CAP_PROP_POS_FRAMES, startFrame);
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
    ui->slider->setValue(ui->adjustSlider->value());
    trackImg.create(frame.size(), frame.type());
    trackImg = Scalar::all(0);
    lock = true;

    // Variaveis ------------
    Mat frame2, frame_tmp, movement;
    const int margin = 15, learnSizeCount = 100, nPts = 50;
    int movementCount = 0, smallObjectArea = 0;
    int gtIndexContour = 0;
    float avArea, avAreaSum = 0;
    bool isCalibrated = false;
    vector<vector<Point>> contours, contours_poly, movementContours;
    vector<Point> pts[nPts];
    vector<Vec4i> hierarchy, movementHierarchy;
    vector<Rect> boundRect;
    vector<Moments> mu;                // moments
    vector<Point2f> mc;                // centro
    vector<Point> trackPath, lastContour;
    uchar value;
    vector<float> area;

    // mapeamento da orientacao da cobaia
    const int orientationDist = 30;  //        30 pixels
    Point firstOrientationPoint;    // ponto1 <---------> ponto2
    Mat orientationMap;             // mapa contendo as direcoes

    //           Cores:
    const Scalar red   = Scalar(255, 0, 0),
                 cyan  = Scalar(0, 255, 255);
    // ----------------------

    while(video.isOpened())
    {
        video >> frame;
        value = ui->slider->value();
        ui->progressBar->setValue(video.get(CAP_PROP_POS_FRAMES));

        if(!frame.empty())
        {
            if(!smallObjectArea) smallObjectArea = (frame.rows*frame.cols)*0.003;
            frame.copyTo(frame2, maskZoneGlobal);

            // frame2 - background
            subtract(frame2, background, frame2);

            // Conversao de cores
            cvtColor(frame, frame, COLOR_BGR2RGB);
            cvtColor(frame2, frame2, COLOR_BGR2GRAY);

            // Aplica o threshold
            threshold(frame2, frame2, value, 255, THRESH_BINARY);
            GaussianBlur(frame2, frame2, Size(3,3), 0, 0);

            // Deteccao de movimento ------------------------------------------
            if(movementCount == 1){
                frame2.copyTo(frame_tmp);
            }else if(movementCount == 10){
                subtract(frame2, frame_tmp, movement);
                movementCount = 0;
            }   movementCount++;

            findContours(movement, movementContours, movementHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

            vector<Rect> movementBoundRect = vector<Rect>(movementContours.size());
            Point2f movementCenter;
            if(movementContours.size() > 0){
                sortContours(movementContours);

                for(uint i=0; i<movementContours.size(); i++){
                    movementBoundRect[i] = boundingRect( Mat(movementContours[i]) );
                    if(ui->checkShowMovement->isChecked())
                        drawContours(frame, movementContours, i, CV_RGB(255,0,204), 2, 8, hierarchy, 0, Point());
                }

                Moments movementMoment = moments(movementContours[0], false);
                movementCenter = Point2f(movementMoment.m10 / movementMoment.m00,
                                         movementMoment.m01 / movementMoment.m00);
            }
            // ----------------------------------------------------------------


            // Encontra e desenha os contornos ------------------------------------------------------------------------
            findContours(frame2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

            // organiza os contornos por maior area
            sortContours(contours);
            // remove os contornos com area pequena
            for(uint i=0; i<contours.size(); i++){
                if(contourArea(contours[i]) < smallObjectArea){
                    contours.erase(contours.begin() + i, contours.end());
                    break;
                }
            }

            // usa a ultima posicao caso nao haja contornos
            if(contours.empty() && !lastContour.empty()){
                contours.push_back(lastContour);
            }

            contours_poly = vector<vector<Point>>(contours.size());
            boundRect = vector<Rect>(contours.size());
            mu = vector<Moments>(contours.size());
            mc = vector<Point2f>(contours.size());
            // Elipses e retangulos rotacionados para ocupar a menor area possivel
            vector<RotatedRect> minRect( contours.size() );
            vector<RotatedRect> minEllipse( contours.size() );

            for(uint i=0; i<contours.size(); i++){
                approxPolyDP( contours[i], contours_poly[i], 0.005 * arcLength(contours[i], true), true );
                boundRect[i] = boundingRect( Mat(contours_poly[i]) );
                mu[i] = moments(contours_poly[i], false);
                mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
                minRect[i] = minAreaRect( Mat(contours[i]) );
                if( contours[i].size() > 5 ){
                    minEllipse[i] = fitEllipse( Mat(contours[i]) );
                }
            }


            if(!contours.empty())
            {
                gtIndexContour = 0;

                if(pts[0].size() == learnSizeCount-1)
                {
                    if(!isCalibrated){
                        isCalibrated = true;
                        for(uint i=1; i<pts[0].size()+1; i++){
                            float ptDistance = norm(pts[0][i] - pts[0][i+1]);
                            if (ptDistance > 5){
                                pts[0].erase(pts[0].begin()+i);
                                i--;
                            }
                        }
                    }

                    // remove o primeiro ponto caso o vetor atinja o limite
                    for(int i=0; i<nPts; i++)
                        pts[i].erase(pts[i].begin());

                    avAreaSum -= area[0];
                    area.erase(area.begin());
                }

                if(!isCalibrated) putText(frame, "Calibrando", Point(0, frame.rows), FONT_HERSHEY_PLAIN, 4, red, 3);


                // adiciona os valores ao vetor de pontos -----------------------------------------
                for(uint i=0; i<nPts; i++){
                    if(contours.size() > gtIndexContour + i)
                        pts[i].push_back(mc[gtIndexContour + i]);
                    else pts[i].push_back(mc[gtIndexContour]);

                    if(pts[i].size() > 1)
                        if(abs(norm(pts[i][pts[i].size()-1] - pts[i][pts[i].size()-2])) < 0.02){
                            pts[i].pop_back();
                        }
                } // ------------------------------------------------------------------------------


                // precisao -----------------------------------------------------------------
                float gtQ = 0, Q;

                if(pts[0].size() > 0)
                {
                    for(uint i=0; i<nPts; i++){
                        if((contours.size() > i))
                        {
                            float mdistance = abs(norm(pts[i][pts[i].size()-1] - Point(movementCenter)));
                            Q = 1/((matchShapes(animalContour, contours_poly[i], 1, 0.0) + mdistance)/2);

                            if( Q > gtQ ){
                                gtQ = Q;
                                gtIndexContour = i;
                                pts[0][pts[0].size()-1] = pts[i][pts[i].size()-1];
                            }

                            //ui->statusBar->showMessage(QString::number(contours.size()) + " " + QString::number(gtQ));
                        }//else break;
                    }
                } // ------------------------------------------------------------------------------

                // area media da cobaia (precisa estar depois do anti-teleporte)
                float currentArea = contourArea(contours_poly[gtIndexContour]);
                area.push_back(currentArea);
                avAreaSum += currentArea;
                avArea = avAreaSum / area.size();

                // ----------------------------------------------------------------------------------------------------


                //trajeto
                if(ui->checkCreateTrackMap->isChecked() && pts[0].size() > 1 && isCalibrated){
                    uint trackColor = (((video.get(CAP_PROP_POS_FRAMES) - startFrame)*255)/endFrame);
                    line(trackImg, pts[0][1], pts[0][2], Scalar(trackColor,0,255-trackColor), 2);
                }
                if(ui->checkShowTrack->isChecked()){
                    polylines(frame, pts[6], false, CV_RGB(255,255,255), 1);
                    polylines(frame, pts[5], false, CV_RGB(0,255,255), 1);
                    polylines(frame, pts[4], false, CV_RGB(255,0,255), 1);
                    polylines(frame, pts[3], false, CV_RGB(255,255,0), 1);
                    polylines(frame, pts[2], false, CV_RGB(0,0,255), 1);
                    polylines(frame, pts[1], false, CV_RGB(255,0,0), 1);
                    polylines(frame, pts[0], false, CV_RGB(0,255,0), 3);
                }

                //contorno:
                if(ui->checkShowContour->isChecked())
                    drawContours(frame, contours_poly, gtIndexContour, CV_RGB(0,140,255), 2, 8, hierarchy, 0, Point());

                //boundingbox:
                if(ui->checkShowRect->isChecked())
                {
                    // Bounding box
                    rectangle(frame, Point(boundRect[gtIndexContour].tl().x - margin, boundRect[gtIndexContour].tl().y - margin),
                                     Point(boundRect[gtIndexContour].br().x + margin, boundRect[gtIndexContour].br().y + margin),
                                     cyan, 2, 8, 0);

                    // Elipse + Retangulo rotacionados
                    ellipse( frame, minEllipse[gtIndexContour], cyan, 2, 8 );
                    Point2f rect_points[4]; minRect[gtIndexContour].points( rect_points );

                    for( int j = 0; j < 4; j++ )
                        line( frame, rect_points[j], rect_points[(j+1)%4], cyan, 1, 8 );

                    //orientacao
                    if(orientationMap.empty()) orientationMap.create(frame.size(), frame.type());

                    uint quad;

                    if(norm(firstOrientationPoint - pts[0][pts[0].size()-1]) > orientationDist){
                        quad = getQuad(firstOrientationPoint, pts[0][pts[0].size()-1]);
                        arrowedLine(orientationMap, firstOrientationPoint, pts[0][pts[0].size()-1], CV_RGB(255,255,0), 2);
                        firstOrientationPoint = pts[0][pts[0].size()-1];
                    }
                    if(quad & 1){
                        line(frame, Point(frame.cols/2, 0), Point(frame.cols, 0), CV_RGB(0,0,255), 8);
                        line(frame, Point(frame.cols, 0), Point(frame.cols, frame.rows/2), CV_RGB(0,0,255), 8);
                    }
                    if(quad & 2){
                        line(frame, Point(frame.cols, frame.rows/2), Point(frame.cols, frame.rows), CV_RGB(0,0,255), 8);
                        line(frame, Point(frame.cols, frame.rows), Point(frame.cols/2, frame.rows), CV_RGB(0,0,255), 8);
                    }
                    if(quad & 4){
                        line(frame, Point(frame.cols/2, frame.rows), Point(0, frame.rows), CV_RGB(0,0,255), 8);
                        line(frame, Point(0, frame.rows), Point(0, frame.rows/2), CV_RGB(0,0,255), 8);
                    }
                    if(quad & 8){
                        line(frame, Point(0, frame.rows/2), Point(0, 0), CV_RGB(0,0,255), 8);
                        line(frame, Point(0, 0), Point(frame.cols/2, 0), CV_RGB(0,0,255), 8);
                    }
                }

                //centro
                if(ui->checkShowPoint->isChecked())
                    circle(frame, pts[0][pts[0].size()-1], 5, red, -1, 8, 0);



                //TEXTO:
                string text = "";

                //identificacao da cobaia
                if(ui->chechShowId->isChecked())
                    text += "Rato : ";

                //distancia percorrida
                trackPath.push_back(pts[0][pts[0].size()-1]);
                if(ui->checkShowDistance->isChecked())
                    text += to_string(arcLength(trackPath, false)/pixelsPerMeter) + " m";

                putText(frame,
                        text ,
                        Point(boundRect[gtIndexContour].tl().x - margin, boundRect[gtIndexContour].tl().y - margin - 5),
                        FONT_HERSHEY_PLAIN, 1.5, CV_RGB(0,140,255), 2);

                // copia o contorno da cobaia
                lastContour = contours[gtIndexContour];
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
            if(ui->alternativeViewSelector->currentText() == "movimento") frameAlternative = &movement;
            if(ui->alternativeViewSelector->currentText() == "trajeto") frameAlternative = &trackImg;
            if(ui->alternativeViewSelector->currentText() == "orientação") frameAlternative = &orientationMap;

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
            if(video.get(CAP_PROP_POS_FRAMES) == endFrame){
                video.release();
                ui->startBtn->setText("Reiniciar Análise");
            }

            // reseta a trajetoria
            if(ui->btnResetTrack->isDown()){
                for(int i=0; i<nPts; i++)
                    pts[i].clear();
            }
        }
        qApp->processEvents();
        while(ui->pauseBtn->isChecked()){
            ui->pauseBtn->setText("Continuar Análise");
            qApp->processEvents();
            if(ui->nextBtn->isDown()) break;
        }   ui->pauseBtn->setText("Pausar Análise");
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
        video.set(CAP_PROP_POS_FRAMES, ui->framePosSlider->value());
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

    if(mode == MODE_ANIMAL_SELECT){
        mode = MODE_ANIMAL_EDIT;
        tool = -1;

        ui->graphicsView->setSceneRect(0, 0, frame(Rect(selectPoints[0], selectPoints[1])).cols,
                                             frame(Rect(selectPoints[0], selectPoints[1])).rows);
        ui->graphicsViewAlternative->setSceneRect(0, 0, frame(Rect(selectPoints[0], selectPoints[1])).cols,
                                                        frame(Rect(selectPoints[0], selectPoints[1])).rows);

        ui->actionToolRectangle->setEnabled(false);
        ui->adjustBox->show();
        return;
    }

    if(mode == MODE_ANIMAL_EDIT){
        ui->graphicsView->setSceneRect(0, 0, frame.cols, frame.rows);
        ui->graphicsViewAlternative->setSceneRect(0, 0, frame.cols, frame.rows);
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
    ui->adjustBox->hide();
    mode = MODE_DEFAULT;
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

void MainWindow::on_btnAnimalSelect_pressed()
{
    ui->actionToolRectangle->trigger();
    ui->confirmBox->show();
    ui->actionAbrirVideo->setEnabled(false);
    ui->actionToolCircle->setEnabled(false);
    ui->actionToolLine->setEnabled(false);
    ui->actionToolArrow->setEnabled(false);
    ui->actionToolPolygon->setEnabled(false);

    mode = MODE_ANIMAL_SELECT;
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

