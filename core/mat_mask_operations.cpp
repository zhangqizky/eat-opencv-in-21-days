//
//  mat_mask_operations.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/9/18.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;

static void help(char * progName)
{
    cout << endl
    << "此程序是展示如何使用对矩阵做卷积操作，分别用自己写的函数和opencv自带的函数去做";
}

void Sharpen(const Mat& myImage,Mat& Result);

int main(int argc,char**argv)
{
    help(argv[0]);
    const char* filename = argc>=2?argv[1]:"lena.jpg";
    
    Mat src,dst0,dst1;
    if(argc >= 3 &&!strcmp("G",argv[2]))
        src = imread( samples::findFile( filename ), IMREAD_GRAYSCALE);
    else
        src = imread( samples::findFile( filename ), IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Can't open image ["  << filename << "]" << endl;
        return EXIT_FAILURE;
    }
    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    imshow( "Input", src );
    double t = (double)getTickCount();
    
    //自己写的锐化函数
    Sharpen(src, dst0);
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "自己手写函数的耗时: " << t << endl;

    imshow( "Output", dst0 );
    waitKey();
    
    
    Mat kernel = (Mat_<char>(3,3) << 0,-1,0,
                                    -1,5,-1,
                                    0,-1,0);
    
    t = (double)getTickCount();
    filter2D(src, dst1, src.depth(), kernel);
    
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "OpenCV自带滤波函数的耗时:     " << t << endl;

    imshow( "Output", dst1 );

    waitKey();
}

void Sharpen(const Mat& myImage,Mat& Result)
{
    //! [8_bit]
      CV_Assert(myImage.depth() == CV_8U);  // 只接受CV_8U类型的数据
    //! [8_bit]
    
    const int nChannels = myImage.channels();
    Result.create(myImage.size(), myImage.type());
    
    for (int j = 1;j<myImage.rows-1;++j)
    {
        const uchar*previous = myImage.ptr<uchar>(j-1);
        const uchar*current = myImage.ptr<uchar>(j  );
        const uchar*next =myImage.ptr<uchar>(j +1);
        
        uchar*output = Result.ptr<uchar>();
        for (int i = nChannels;i < nChannels*(myImage.cols -1);++i)
        {
            *output++ = saturate_cast<uchar>(5*current[i] - current[i-nChannels]-current[i+nChannels]-previous[i]-next[i]);
        }
    }
    
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
    
}
