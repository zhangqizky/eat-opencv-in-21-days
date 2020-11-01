#include <stdio.h>

#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ContrastImageCorrection(const Mat & src,Mat&dst)
{
    int rows = src.rows;
    int cols = src.cols;
    
    Mat yuvImage;
    cvtColor(src, yuvImage, COLOR_BGR2YUV);
    vector<Mat>mv;
    split(yuvImage, mv);
    Mat oldY = mv[0].clone();
    
    Mat temp;
    bilateralFilter(mv[0], temp, 9, 50, 50);
    for (int i =0;i<rows;i++)
    {
        for(int j =0;j<cols;j++)
        {
            float Exp = pow(2,(128-(255-temp.at<uchar>(i,j))) / 128.0);
            int value = int(255 * pow(oldY.at<uchar>(i,j) / 255.0,Exp));
            temp.at<uchar>(i,j) = value;
        }
    }
    dst.create(rows, cols, CV_8UC3);
    
    for(int i =0;i<rows;i++)
    {
        for(int j =0;j<cols;j++)
        {
            if(oldY.at<uchar>(i,j) == 0)
            {
                for(int k =0;k<3;k++)
                {
                    dst.at<Vec3b>(i,j)[k] = 0;
                }
            }
            else
            {
                dst.at<Vec3b>(i,j)[0] =
                (temp.at<uchar>(i,j) * (src.at<Vec3b>(i,j)[0] + oldY.at<uchar>(i,j)) / oldY.at<uchar>(i,j) + src.at<Vec3b>(i,j)[0] - oldY.at<uchar>(i,j)) >> 1;
                
                dst.at<Vec3b>(i,j)[1] =
                (temp.at<uchar>(i,j) * (src.at<Vec3b>(i,j)[1] + oldY.at<uchar>(i,j)) / oldY.at<uchar>(i,j) + src.at<Vec3b>(i,j)[1] - oldY.at<uchar>(i,j)) >> 1;
                
                dst.at<Vec3b>(i,j)[2] =
                (temp.at<uchar>(i,j) * (src.at<Vec3b>(i,j)[2] + oldY.at<uchar>(i,j)) / oldY.at<uchar>(i,j) + src.at<Vec3b>(i,j)[2] - oldY.at<uchar>(i,j)) >> 1;
            }
        }
    }
}
