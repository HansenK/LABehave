using namespace cv;
using namespace std;

//#include "mainwindow.h"

void poster(Mat& src, Mat& dst, uchar value)
{
    if(!value) value = 1;

    for(int i = 0; i < src.rows; i++){
        for(int j = 0; j < src.cols; j++){
            dst.at<uchar>(i,j) = ((int)src.at<uchar>(i,j)/value)*value;
        }
    }
}

void passaFaixa(Mat& src, Mat& dst, uchar start, uchar end, uchar changeTo = 0)
{
    for(int i = 0; i < src.rows; i++){
        for(int j = 0; j < src.cols; j++){
            if(dst.at<uchar>(i,j) >= start && dst.at<uchar>(i,j) <= end)
                dst.at<uchar>(i,j) = changeTo;
        }
    }
}

void sortContours(vector<vector<Point>>& contours){
    auto contourComparator = [](vector<Point> a, vector<Point> b){ return contourArea(a) > contourArea(b); };
    sort(contours.begin(), contours.end(), contourComparator);
}
