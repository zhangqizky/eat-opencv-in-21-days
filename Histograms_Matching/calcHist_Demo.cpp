//
//  Hist.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/10/17.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("/Users/zhangqi44/Desktop/hehua.jpg");
    
    if(src.empty())
    {
        cerr<<"can not open...."<<endl;
        return -1;
    }
    
    vector<Mat> bgr_planes;
    split(src,bgr_planes);
    cout << bgr_planes.size()<<endl;
    
    int histSize = 256;
    
    float range[] = {0,256};
    const float* histRange ={range};
    
    bool uniform = true,accumulate = false;
    
    Mat b_hist,g_hist,r_hist;
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange,uniform,accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange,uniform,accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange,uniform,accumulate);
    
    int hist_w = 512,hist_h = 400;
    //每个bin的宽度，等于直方图的宽度除以所要分的bins的数目，后者对像素直方图来说就是256个
    int bin_w = cvRound((double)hist_w/ histSize);
    
    Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(255,255,255));
    
    normalize(b_hist,b_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
    normalize(g_hist,g_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
    normalize(r_hist,r_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
    
    for(int i = 1;i < histSize; i++)
    {
        line(histImage, Point(bin_w *(i-1),hist_h - cvRound(b_hist.at<float>(i-1))),
             Point(bin_w*(i),hist_h - cvRound(b_hist.at<float>(i))),
             Scalar(255,0,0),2,8,0);
        line(histImage, Point(bin_w *(i-1),hist_h - cvRound(g_hist.at<float>(i-1))),
             Point(bin_w*(i),hist_h - cvRound(g_hist.at<float>(i))),
             Scalar(0,255,0),2,8,0);
        line(histImage, Point(bin_w *(i-1),hist_h - cvRound(r_hist.at<float>(i-1))),
             Point(bin_w*(i),hist_h - cvRound(r_hist.at<float>(i))),
             Scalar(0,0,255),2,8,0);
    }
    imshow("Source image",src);
    imshow("calcHist Demo",histImage);
    waitKey();
    return 0;
}
