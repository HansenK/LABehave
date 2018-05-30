using namespace cv;
using namespace std;

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

void getBackground(VideoCapture& video, Mat& dst, uint samples = 10)
{
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>();
    Mat frame, foregroundMask;

    video.set(CAP_PROP_POS_FRAMES, 0);
    video >> frame;
    foregroundMask.create(dst.size(), dst.type());

    for(uint i=0; i<samples; i++){
        video.set(CAP_PROP_POS_FRAMES, (video.get(CAP_PROP_FRAME_COUNT)/samples)*i);
        video >> frame;
        bg_model->apply(frame, foregroundMask);
        //addWeighted(dst, 0.9, frame, 0.1, 0, dst);
    }

    bg_model->getBackgroundImage(dst);
    video.set(CAP_PROP_POS_FRAMES, 0);
}
