using namespace cv;
using namespace std;

#include "mainwindow.h"


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

double contourAngle( vector<Point> contour)
{
    double dx1, dy1, dx2, dy2, angle = 0;
    for(uint i=1; i<contour.size()-1; i++)
    {
        dx1 = contour[i-1].x - contour[i].x;
        dy1 = contour[i-1].y - contour[i].y;
        dx2 = contour[i+1].x - contour[i].x;
        dy2 = contour[i+1].y - contour[i].y;

        angle += abs( (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10) );
    }

    return angle;
}


cv::Point2f rotatePoint(const cv::Point2f& inPoint, const cv::Point2f& center, const double& rotAngle)
{
    cv::Mat rot = cv::getRotationMatrix2D(center, rotAngle, 1.0);
    float cos = rot.at<double>(0,0);
    float sin = rot.at<double>(0,1);
    int newWidth = int( ((center.y*2)*sin) +  ((center.x*2)*cos) );
    int newHeight = int( ((center.y*2)*cos) +  ((center.x*2)*sin) );

    rot.at<double>(0,2) += newWidth/2.0 - center.x;
    rot.at<double>(1,2) += newHeight/2.0 - center.y;

    int v[3] = {static_cast<int>(inPoint.x),static_cast<int>(inPoint.y),1};
    int mat3[2][1] = {{0},{0}};

    for(int i=0; i<rot.rows; i++)
    {
        for(int j=0; j<= 0; j++)
        {
            int sum=0;
            for(int k=0; k<3; k++)
            {
                sum = sum + rot.at<double>(i,k) * v[k];
            }
            mat3[i][j] = sum;
        }
    }
    return Point2f(mat3[0][0],mat3[1][0]);
}

int getQuad(cv::Point p1, cv::Point p2){
    int quad = 0b1111;

    // 4 | 1
    // - - -
    // 3 | 2

    if(p2.x - p1.x >  20) quad &= 0b0011;
    if(p2.x - p1.x < -20) quad &= 0b1100;
    if(p2.y - p1.y >  20) quad &= 0b0110;
    if(p2.y - p1.y < -20) quad &= 0b1001;

    return quad;
}
