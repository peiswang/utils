//#include <opencv2/highgui.hpp>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    string src_video = "in.avi";
    string dst_video = "out.avi";

    VideoCapture inputVideo(src_video);
    if(!inputVideo.isOpened())
    {
        cout<<"Open src video error!"<<endl;
        return -1;
    }

    int frame_num = inputVideo.get(CV_CAP_PROP_FRAME_COUNT);
    double fps = inputVideo.get(CV_CAP_PROP_FPS);
    int width = inputVideo.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout<<"frames: "<<frame_num<<endl;
    cout<<"fps: "<<inputVideo.get(CV_CAP_PROP_FPS)<<endl;
    cout<<"resolution: "<<width<<"x"<<height<<endl;

    Size size = Size(width, height);

    VideoWriter outputVideo;
    outputVideo.open(dst_video, 0, 25.0, size, true);
    if(!outputVideo.isOpened())
    {
        cout<<"Open dst video error!"<<endl;
        return -1;
    }

    int count = 0;
    Mat frame;
    vector<Mat> bgr;
    Mat res;
    while(1)
    {
        inputVideo>>frame;
        if(!frame.empty()){
            count++;
            imshow("src", frame);
            split(frame, bgr);
            for(int i=0;i<3;i++)
            {
                if(i>0)
                {
                    bgr[i] = Mat::zeros(size, bgr[0].type());
                }
                merge(bgr, res);
            }
            imshow("dst", res);
            outputVideo<<res;
        }
        else
        {
            break;
        }
        int c = waitKey(33);
        if(c==27)
            break;
    }
    system("pause");
    return 0;
}
