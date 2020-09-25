//
//  Threshold.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/9/25.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using std::cout;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

//两个trackbar，第一个调节类型，第二个调节阈值
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";


static void Threshold_Demo(int,void*)
{
    /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
    
    threshold(src_gray, dst, threshold_value, max_binary_value,threshold_type);
    imshow(window_name,dst);
}

int main(int argc,char**argv)
{
    String imageName("IMG_4200.JPG"); // by default
    if (argc > 1)
    {
        imageName = argv[1];
    }
    src = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Load an image

    if (src.empty())
    {
        cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }
    
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    
    namedWindow(window_name,WINDOW_AUTOSIZE);
    
    createTrackbar(trackbar_value, window_name, &threshold_value, max_value,Threshold_Demo);
    
    createTrackbar(trackbar_type, window_name, &threshold_type, max_type,Threshold_Demo);
    
    Threshold_Demo(0, 0);
    
    waitKey();
    return 0;
    
}
