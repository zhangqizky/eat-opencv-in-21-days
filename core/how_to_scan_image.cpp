//
//  how_to_scan_image.hpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/9/17.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#ifndef how_to_scan_image_hpp
#define how_to_scan_image_hpp

#include <stdio.h>

#endif /* how_to_scan_image_hpp */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "\n--------------------------------------------------------------------------" << endl
        << "本程序主要是用几种不同的方法去访问Mat对象的中的每一个数据，即图像的每一个像素和一些测试用例"
        << " we take an input image and divide the native color palette (255) with the "  << endl
        << "input. Shows C operator[] method, iterators and at function for on-the-fly item address calculation."<< endl
        << "Usage:"                                                                       << endl
        << "./how_to_scan_images <imageNameToUse> <divideWith> [G]"                       << endl
        << "if you add a G parameter the image is processed in gray scale"                << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}


Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

int main(int argc,char*argv[])
{
    help();
    if (argc < 3)
    {
        cout<<"Not enough parameters"<<endl;
        return -1
    }
    
    Mat I,J;
    if(argc == 4 && !strcmp(argv[3],"G"))
        I = imread(argv[1],IMREAD_GRAYSCALE);
    else
        I = imread(argv[1],IMREAD_COLOR);
    
    if (I.empty())
    {
        cout <<"The image"<<argv[1]<<"could not be loaded."<<endl;
        return -1;
    }
    
    //将输入的字符转为整数
    int divideWith = 0;
    stringstream s;
    s << argv[2];
    s >> divideWith;
    
    uchar table[256];
    for(int i =0;i<256;++i)
    {
        table[i] = (uchar)(divideWith * (i/divideWith));
    }
    
    const int times = 100;
    double t;
    
    t = (double)getTickCount();
    
    for (int i = 0;i < times; ++i)
    {
        Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
    }
    
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;
    
    cout << "Time of reducing with the C operator [] (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;
    
    t = (double)getTickCount();
    
    for(int i =0;i < times;++i)
    {
        Mat clone_i = I.clone();
        J = ScanImageAndReduceIterator(clone_i, table);
    }
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the iterator (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        ScanImageAndReduceRandomAccess(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;
    
    
    Mat lookUpTable(1, 256, CV_8U);
    uchar*p = lookUpTable.ptr();
    for (int i = 0;i<times;++i)
    {
        LUT(I,lookUpTable,J);
    }
    
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;
    
    cout << "Time of reducing with the LUT function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;
    
    return 0;
}
