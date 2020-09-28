//
//  periodic_noise_removing_filter.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/9/28.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void fftshift(const Mat& inputImg,Mat& outputImg);
void filter2DFreq(const Mat& inputImg,Mat& outputImg,const Mat& H);
void synthesizeFilterH(Mat& inputOutput_H, Point center, int radius);
void calcPSD(const Mat& inputImg, Mat& outputImg, int flag = 0);

int main()
{
    cout << (19 & -2)<< endl;
    Mat imgIn = imread("input.jpg",IMREAD_GRAYSCALE);
    if (imgIn.empty())
    {
        cout << "ERROR : Image cannot be loaded..!"<<endl;
        return -1;
    }
    //任何计算前最好将图像转为浮点数
    imgIn.convertTo(imgIn, CV_32F);
    
    //找到图像的最大的一个子图，其长和宽都能被2整除
    Rect roi = Rect(0,0,imgIn.cols & -2,imgIn.rows &-2);
    imgIn = imgIn(roi);
    
    Mat imgPSD;
    calcPSD(imgIn, imgPSD);
    fftshift(imgPSD, imgPSD);
    normalize(imgPSD,imgPSD,0,255,NORM_MINMAX);
    
    Mat H = Mat(roi.size(), CV_32F, Scalar(1));
    const int r = 21;
    synthesizeFilterH(H, Point(705, 458), r);
    synthesizeFilterH(H, Point(850, 391), r);
    synthesizeFilterH(H, Point(993, 325), r);
    
    Mat imgOut;
    fftshift(H, H);
    filter2DFreq(imgIn, imgOut, H);
    
    imgOut.convertTo(imgOut, CV_8U);
    normalize(imgOut,imgOut,0,255,NORM_MINMAX);
    imwrite("result.jpg",imgOut);
    imwrite("PSD.jpg",imgPSD);
    fftshift(H, H);
    normalize(H,H,0,255,NORM_MINMAX);
    imwrite("filter.jpg",H);
    return 0;
}

//fftshift，将图像分成四块，对角线的块进行互换
void fftshift(const Mat& inputImg, Mat& outputImg)
{
    outputImg = inputImg.clone();
    int cx = outputImg.cols / 2;
    int cy = outputImg.rows / 2;
    Mat q0(outputImg, Rect(0, 0, cx, cy));
    Mat q1(outputImg, Rect(cx, 0, cx, cy));
    Mat q2(outputImg, Rect(0, cy, cx, cy));
    Mat q3(outputImg, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H)
{
    Mat planes[2] = {Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(),CV_32F)};
    Mat complexI;
    merge(planes,2,complexI);
    dft(complexI,complexI,DFT_SCALE);
    
    Mat planesH[2] = { Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F) };
    Mat complexH;
    merge(planesH, 2, complexH);
    Mat complexIH;
    mulSpectrums(complexI, complexH, complexIH, 0);
    
    idft(complexIH,complexIH);
    split(complexIH, planes);
    outputImg =  planes[0];
}

void synthesizeFilterH(Mat& inputOutput_H, Point center, int radius)
{
    Point c2 = center, c3 = center, c4 = center;
    c2.y = inputOutput_H.rows - center.y;
    c3.x = inputOutput_H.cols - center.x;
    c4 = Point(c3.x,c2.y);
    circle(inputOutput_H, center, radius, 0, -1, 8);
    circle(inputOutput_H, c2, radius, 0, -1, 8);
    circle(inputOutput_H, c3, radius, 0, -1, 8);
    circle(inputOutput_H, c4, radius, 0, -1, 8);
}

void calPSD(const Mat& inputImg,Mat& outputImg,int flag)
{
    Mat planes[2] = { Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);
    
    dft(complexI,complexI);
    split(complexI, planes);
    
    planes[0].at<float>(0) = 0;
    planes[1].at<float>(0) = 0;
    
    Mat imgPSD;
    magnitude(planes[0], planes[1], imgPSD);
    pow(imgPSD,2,imgPSD);
    outputImg = imgPSD;
    
    if(flag)
    {
        Mat imglogPSD;
        imglogPSD = imglogPSD + Scalar::all(1);
        log(imglogPSD,imglogPSD);
        outputImg = imglogPSD;
    }
 }
