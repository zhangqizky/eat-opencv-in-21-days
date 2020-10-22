//
//  splitGuassian.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/10/21.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<math.h>
 
using namespace cv;
using namespace std;
 
 
void getGaussianArray(vector<double>& gauss_arry, const double& sigma) {
    int i;
    int arr_size = gauss_arry.size();
    int center_i = arr_size / 2;
    double sum = 0.0f;
    for (i = 0; i < arr_size; ++i) {
        gauss_arry[i] = exp(-(1.0f)* (((i - center_i)*(i - center_i)) /
            (2.0f*sigma*sigma)));
        sum += gauss_arry[i];
    }
    for (i = 0; i < arr_size; ++i)
        gauss_arry[i] /= sum;
}
 
void gaussian(Mat& src, vector<double>& arrayX, vector<double>& arrayY) {
    int center = arrayX.size() / 2;
    Mat temp = src.clone();
 
    // 先x轴方向计算
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            if (i > center - 1 && j > center - 1 && i < src.rows - center && j < src.cols - center) {
                double sum = 0.0;
                for (int l = 0; l < arrayX.size(); ++l)
                    sum += src.ptr<uchar>(i)[j - l + center] * arrayX[l];
                temp.ptr<uchar>(i)[j] = MAX(MIN(sum, 255), 0);
            }
        }
    }
 
    // 接着y轴方向计算
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            if (i > center - 1 && j > center - 1 && i < src.rows - center && j < src.cols - center) {
                double sum = 0.0;
                for (int k = 0; k < arrayX.size(); ++k)
                    sum += temp.ptr<uchar>(i - k + center)[j] * arrayY[k];
                src.ptr<uchar>(i)[j] = MAX(MIN(sum, 255), 0);
            }
        }
    }
}
 
void splitGaussianFilterFast(Mat& src, Mat& dst, int n, double sigmaX, double sigmaY)
{
    vector<double>arrayX(n);
    vector<double>arrayY(n);
    vector<cv::Mat> channels;
    dst = src.clone();
    cv::split(src, channels);
    getGaussianArray(arrayX, sigmaX);
    getGaussianArray(arrayY, sigmaY);
    for (int i = 0; i < 3; i++) {
        gaussian(channels[i], arrayX, arrayY);
    }
    cv::merge(channels, dst);
}
 
int main(void)
{
    cv::Mat src = cv::imread("/Users/zhangqi44/Desktop/hehua.jpg");
    cv::Mat dst;
    cv::Mat dst2;
    double time0 = static_cast<double>(getTickCount());
    splitGaussianFilterFast(src, dst, 3, 2.0f, 2.0f);
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "分离卷积高斯方法运行时间为：" << time0 << "秒" << endl;
 
    time0 = static_cast<double>(getTickCount());
    GaussianBlur(src, dst2, cv::Size(3, 3), 2.0f, 2.0f);
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "Opencv自带方法运行时间为：" << time0 << "秒" << endl;
 
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::imshow("dst2", dst2);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
