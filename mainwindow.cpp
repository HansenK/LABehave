#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Mat image = imread("C:\\Users\\Hansen\\TCC\\img1.jpg", 1);
    Mat img_gray, img_thresh;

    cvtColor(image, img_gray, COLOR_BGR2GRAY); // Converte a imagem para tons de cinza
    threshold(img_gray, img_thresh, 100, 255, 3);

    namedWindow("My Image");
    if (!image.empty()) imshow("My Image", img_thresh);

}

MainWindow::~MainWindow()
{
    delete ui;
}
