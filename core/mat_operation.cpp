/*  Snippet code for Operations with images tutorial (not intended to be run but should built successfully) */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int,char**)
{
    //待处理图像路径
    std::string filename = "";
    
    // 读取输入图像
    {
        //! [Load an image from a file]
        Mat img = imread(filename);
        //! [Load an image from a file]
        CV_UNUSED(img);
    }
    
    {
        //! [用灰度模式载入图像]
        Mat img = imread(filename, IMREAD_GRAYSCALE);
        //! [Load an image from a file in grayscale]
        CV_UNUSED(img);
    }
    {
        Mat img(4,4,CV_8U);
        //! [Save image]
        imwrite(filename, img);
        //! [Save image]
    }
    // 获取图像的像素值,用 at<uchar>(y,x),y代表的是行坐标，也就是height，x代表的是列坐标，也就是width
    {
        Mat img(4,4,CV_8U);
        int y = 0, x = 0;
        {
            //! [像素值 获取方法1 ]
            Scalar intensity = img.at<uchar>(y, x);
            //! [Pixel access 1]
            CV_UNUSED(intensity);
        }
        {
            //! [像素值获取方法 2]
            Scalar intensity = img.at<uchar>(Point(x, y));
            //! [Pixel access 2]
            CV_UNUSED(intensity);
        }
        {
            //! [像素值获取方法 3]
            Vec3b intensity = img.at<Vec3b>(y, x);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            //! [Pixel access 3]
            CV_UNUSED(blue);
            CV_UNUSED(green);
            CV_UNUSED(red);
        }
        {
            //! [像素获取方法 4，获取float类型的像素值]
            Vec3f intensity = img.at<Vec3f>(y, x);
            float blue = intensity.val[0];
            float green = intensity.val[1];
            float red = intensity.val[2];
            //! [Pixel access 4]
            CV_UNUSED(blue);
            CV_UNUSED(green);
            CV_UNUSED(red);
        }
        {
            //! [像素获取方式 5，修改像素值]
            img.at<uchar>(y, x) = 128;
            //! [Pixel access 5]
        }
        {
            int i = 0;
            //! [从points的vector中构建Mat矩阵，2通道的矩阵]
            vector<Point2f> points;
            //... fill the array
            Mat pointsMat = Mat(points);
            //! [Mat from points vector]

            //! [Point access]
            Point2f point = pointsMat.at<Point2f>(i, 0);
            //! [Point access]
            CV_UNUSED(point);
        }
    }
    // 内存管理和引用计数
    {
        //! [Reference counting 1]
        std::vector<Point3f> points;
        // .. fill the array
        Mat pointsMat = Mat(points).reshape(1);
        //! [Reference counting 1]
        CV_UNUSED(pointsMat);
    }
    {
        //! [Reference counting 2]
        Mat img = imread("image.jpg");
        Mat img1 = img.clone();
        //! [Reference counting 2]
        CV_UNUSED(img1);
    }
    {
        //! [Reference counting 3]
        Mat img = imread("image.jpg");
        Mat sobelx;
        Sobel(img, sobelx, CV_32F, 1, 0);
        //! [Reference counting 3]
    }
    // Primitive operations
    {
        Mat img;
        {
            //! [Set image to black]
            img = Scalar(0);
            //! [Set image to black]
        }
        {
            //! [Select ROI]
            Rect r(10, 10, 100, 100);
            Mat smallImg = img(r);
            //! [Select ROI]
            CV_UNUSED(smallImg);
        }
    }
    {
        //! [BGR to Gray]
        Mat img = imread("image.jpg"); // loading a 8UC3 image
        Mat grey;
        cvtColor(img, grey, COLOR_BGR2GRAY);
        //! [BGR to Gray]
    }
    {
        Mat dst, src;
        //! [Convert to CV_32F]
        src.convertTo(dst, CV_32F);
        //! [Convert to CV_32F]
    }
    // Visualizing images
    {
        //! [imshow 1]
        Mat img = imread("image.jpg");
        namedWindow("image", WINDOW_AUTOSIZE);
        imshow("image", img);
        waitKey();
        //! [imshow 1]
    }
    {
        //! [imshow 2]
        Mat img = imread("image.jpg");
        Mat grey;
        cvtColor(img, grey, COLOR_BGR2GRAY);
        Mat sobelx;
        Sobel(grey, sobelx, CV_32F, 1, 0);
        double minVal, maxVal;
        minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
        Mat draw;
        sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
        namedWindow("image", WINDOW_AUTOSIZE);
        imshow("image", draw);
        waitKey();
        //! [imshow 2]
    }

    return 0;
}
