//
//  motion_deblur_filter.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/9/28.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

/**
 很多书上都用集合论来讲这一变换，对应用者来说似乎没这必要。简单来说击中-击不中运算常用于二值图像，它用于基于结构元素的配置，从图像中寻找具有某种像素排列特征的目标，如单个像素、颗粒中交叉或纵向的特征、直角边缘或其他用户自定义的特征等。计算时，只有当结构元素与其覆盖的图像区域完全相同时，中心像素的值才会被置为1，否则为0。下图给出了一个例子。
 */
int main()
{
    //255代表击中，0代表击不中
    Mat input_image = (Mat_<uchar>(8, 8) <<
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 255, 255, 255, 0, 0, 0, 255,
        0, 255, 255, 255, 0, 0, 0, 0,
        0, 255, 255, 255, 0, 255, 0, 0,
        0, 0, 255, 0, 0, 0, 0, 0,
        0, 0, 255, 0, 0, 255, 255, 0,
        0, 255, 0, 255, 0, 0, 255, 0,
        0, 255, 255, 255, 0, 0, 0, 0);
    
    Mat kernel = (Mat_<int>(3, 3) <<
        0, 1, 0,
        1, -1, 1,
        0, 1, 0);
    Mat output_image;
    morphologyEx(input_image, output_image, MORPH_HITMISS, kernel);
    
    const int rate = 50;
    kernel = (kernel + 1) * 127;
    kernel.convertTo(kernel, CV_8U);

    resize(kernel, kernel, Size(), rate, rate, INTER_NEAREST);
    imshow("kernel", kernel);
    moveWindow("kernel", 0, 0);

    resize(input_image, input_image, Size(), rate, rate, INTER_NEAREST);
    imshow("Original", input_image);
    moveWindow("Original", 0, 200);

    resize(output_image, output_image, Size(), rate, rate, INTER_NEAREST);
    imshow("Hit or Miss", output_image);
    moveWindow("Hit or Miss", 500, 200);

    waitKey(0);
    return 0;
    
}

