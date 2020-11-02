#include <stdio.h>

#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;



/******************************************************
 基于亮度均衡的图像阈值分割技术
 1、如果是RGB图像，需要转换为灰度图；
 2、求取原始图src的平均灰度，并记录rows和cols；
  3、按照一定大小，氛围DX x DY方块，求出每块方块的平均值，得到子块的亮度矩阵D
 4、用矩阵D的每个元素减去原图的平均灰度，得到子块的亮度差值矩阵E
 5、用双立方差值法，将矩阵Eresize成和原图大小一样的亮度分布矩阵R
 6、得到矫正后的图像，result = I - R
 
*********************************************************/

void UnevenLightCompensate(const Mat& src,Mat& dst,int block_size)
{
    int row = src.rows;
    int col = src.cols;
    
    Mat gray;
    if(src.channels() == 3)
    {
        cvtColor(src,gray,COLOR_BGR2GRAY);
    }
    else
    {
        gray = src.clone();
    }
    float average = mean(gray)[0];
    int new_row = ceil(1.0 * row / block_size);
    int new_col = ceil(1.0 * col / block_size);
    Mat new_img(new_row,new_col,CV_32FC1);
    
    for(int i = 0; i < new_row; ++i)
    {
        for(int j = 0; j < new_col; ++j)
        {
            int rowx = i * block_size;
            int rowy = (i+1) * block_size;
            int colx = j*block_size;
            int coly = (j+1)*block_size;
            if(rowy > row) rowy = row;
            if(colx > col) coly = col;
            //在原图上取一块ROI区域
            Mat ROI = src(Range(rowx,rowy),Range(colx,coly));
            float block_average = mean(ROI)[0];
            new_img.at<float>(i,j) = block_average;
        }
    }
    new_img = new_img - average;
    Mat new_img2;
    resize(new_img,new_img2,Size(col,row),(0,0),(0,0),INTER_CUBIC);
    Mat new_src;
    gray.convertTo(new_src,CV_32FC1);
    dst = new_src - new_img2;
    dst.convertTo(dst, CV_8UC1);
}




void ContrastImageCorrection(const Mat & src,Mat&dst)
{
    int rows = src.rows;
    int cols = src.cols;
    
    Mat yuvImage;
    cvtColor(src, yuvImage, COLOR_BGR2YUV);
    vector<Mat>mv;
    split(yuvImage, mv);
    Mat oldY = mv[0].clone();
    
    Mat temp;
    bilateralFilter(mv[0], temp, 9, 50, 50);
    for (int i =0;i<rows;i++)
    {
        for(int j =0;j<cols;j++)
        {
            float Exp = pow(2,(128-(255-temp.at<uchar>(i,j))) / 128.0);
            int value = int(255 * pow(oldY.at<uchar>(i,j) / 255.0,Exp));
            temp.at<uchar>(i,j) = value;
        }
    }
    dst.create(rows, cols, CV_8UC3);
    
    for(int i =0;i<rows;i++)
    {
        for(int j =0;j<cols;j++)
        {
            if(oldY.at<uchar>(i,j) == 0)
            {
                for(int k =0;k<3;k++)
                {
                    dst.at<Vec3b>(i,j)[k] = 0;
                }
            }
            else
            {
                dst.at<Vec3b>(i,j)[0] =
                (temp.at<uchar>(i,j) * (src.at<Vec3b>(i,j)[0] + oldY.at<uchar>(i,j)) / oldY.at<uchar>(i,j) + src.at<Vec3b>(i,j)[0] - oldY.at<uchar>(i,j)) >> 1;
                
                dst.at<Vec3b>(i,j)[1] =
                (temp.at<uchar>(i,j) * (src.at<Vec3b>(i,j)[1] + oldY.at<uchar>(i,j)) / oldY.at<uchar>(i,j) + src.at<Vec3b>(i,j)[1] - oldY.at<uchar>(i,j)) >> 1;
                
                dst.at<Vec3b>(i,j)[2] =
                (temp.at<uchar>(i,j) * (src.at<Vec3b>(i,j)[2] + oldY.at<uchar>(i,j)) / oldY.at<uchar>(i,j) + src.at<Vec3b>(i,j)[2] - oldY.at<uchar>(i,j)) >> 1;
            }
        }
    }
}
