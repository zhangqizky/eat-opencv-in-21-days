//
//  Morphology.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/10/13.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void show_wait_destroy(const char* winname, cv::Mat img) {
    imshow(winname, img);
    moveWindow(winname, 500, 0);
    waitKey(0);
    destroyWindow(winname);
}

int main()
{
    Mat src = imread("test_png7.jpg");
    
    if(src.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        return -1;
    }
    
    imshow("src",src);
    
    
    Mat gray;
    
    if(src.channels() == 3)
    {
        cvtColor(src,gray,COLOR_BGR2GRAY);
    }
    else
    {
        gray = src;
    }
    
    Mat bw;
    //对gray的反
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    
    Mat horizontal = bw.clone();
    Mat vertical = bw.clone();
    
    
    int horizontal_size = horizontal.cols / 30;
    
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size,1));
    
    erode(horizontal,horizontal,horizontalStructure,Point(-1,-1));
    dilate(horizontal, horizontal, horizontalStructure,Point(-1,-1));
    
    int vertical_size = vertical.rows / 30;
    
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(vertical_size,1));
    
    erode(vertical, vertical, verticalStructure,Point(-1,-1));
    dilate(vertical, vertical, verticalStructure,Point(-1,-1));
    
    bitwise_not(vertical, vertical);
    show_wait_destroy("vertical bit", vertical);
    
    // Extract edges and smooth image according to the logic
    // 1. extract edges
    // 2. dilate(edges)
    // 3. src.copyTo(smooth)
    // 4. blur smooth img
    // 5. smooth.copyTo(src, edges)
    
    Mat edges;
    adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
    show_wait_destroy("edges", edges);
    
    Mat kernel = Mat::ones(2,2,CV_8UC1);
    dilate(edges, edges, kernel);
    
    Mat smooth;
    vertical.copyTo(smooth);
    
    blur(smooth,smooth,Size(2,2));
    
    smooth.copyTo(vertical,edges);
    
    show_wait_destroy("smmoth -final", vertical);
    
    return 0;
    
}

