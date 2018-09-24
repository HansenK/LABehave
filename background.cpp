#include "mainwindow.h"
using namespace cv;
using namespace std;

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
