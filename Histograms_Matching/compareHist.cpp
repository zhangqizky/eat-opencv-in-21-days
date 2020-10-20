//
//  compareHist_Demo.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/10/20.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat src_base = imread("input1.jpg");
    Mat src_test1 = imread("input2.jpg");
    Mat src_test2 = imread("input3.jpg");
    
    if(src_base.empty() || src_test1.empty() || src_test2.empty())
    {
        cout << "Could not open or find the images!\n" << endl;
        return -1;
    }
    
    Mat hsv_base, hsv_test1,hsv_test2;
    cvtColor(src_base,src_base,COLOR_BGR2HSV);
    cvtColor(src_test1,src_test1,COLOR_BGR2HSV);
    cvtColor(src_test2, src_test2, COLOR_BGR2HSV);
    
    Mat hsv_half_down = hsv_base(Range(hsv_base.rows/2,hsv_base.rows),Range(0,hsv_base.cols));
    int h_bins = 50,s_bins = 60;
    int histSize[] = {h_bins,s_bins};
    
    float h_ranges[] = {0,180};
    float s_ranges[] = {0,256};
    
    const float* ranges[] = {h_ranges,s_ranges};
    
    int channels[] = {0,1};
    
    Mat hist_base,hist_half_down,hist_test1,hist_test2;
    
    calcHist(&hist_base, 1, channels, Mat(), hist_base, 2, histSize, ranges,true,false);
    normalize(hist_base,hist_base,0,1,NORM_MINMAX,-1,Mat());
    
    calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges,true,false);
    normalize(hist_half_down,hist_half_down,0,1,NORM_MINMAX,-1,Mat());
    
    calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
    normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false );
    normalize( hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat() );
    
    //compareHist的四种方法，主要就是计算两个直方图之间的距离的方案d(H1,H2)
    for(int compare_method = 0;compare_method<4;compare_method++)
    {
        double base_base = compareHist(hist_base, hist_base, compare_method);
        double base_half = compareHist(hist_base, hist_half_down, compare_method);
        double base_test1 = compareHist(hist_base, hist_test1, compare_method);
        double base_test2 = compareHist(hist_base, hist_test2, compare_method);
 
        cout << "Method " << compare_method << " Perfect, Base-Half, Base-Test(1), Base-Test(2) : "
             <<  base_base << " / " << base_half << " / " << base_test1 << " / " << base_test2 << endl;
    }
    
    return 0;
}
