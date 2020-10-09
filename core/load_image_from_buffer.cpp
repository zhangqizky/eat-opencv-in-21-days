//
//  load_image_from_buffer.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/10/9.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include "load_image_from_buffer.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


bool is_image_format(const char * buffer, int bufferlen)
{
    //jpeg
    if ((unsigned char)buffer[0] == 0xFF && (unsigned char)buffer[1] == 0xD8 &&
        ((unsigned char)buffer[bufferlen - 2] != 0xFF ||
        (unsigned char)buffer[bufferlen - 1] != 0xD9))
    {
        return true;
    }
    //png
    else if((unsigned char)buffer[0] == 0x89 &&(unsigned char)buffer[1] == 0x50 &&
            (unsigned char)buffer[2] == 0x4E   && (unsigned char)buffer[3] == 0x47
            )
    {
        cout<<"is png.."<<endl;
        return true;
    }
    //tiff
    else if(((unsigned char)buffer[0] ==0x4D && (unsigned char)buffer[1]==0x4D) ||
        ((unsigned char)buffer[0] ==0x49 && (unsigned char)buffer[1]==0x49))
    {
        return true;
    }
    //bmp
    else if ((unsigned char)buffer[0] == 0x42 && (unsigned char)buffer[1] == 0x4D)
    {
        return true;
    }
    
    return false;
}
cv::Mat loadcvmatfrommem(const char * buffer, int bufferlen, int iscolor)
{
    if (bufferlen <= 4) {
        return cv::Mat();
    }
    if(!is_image_format(buffer,bufferlen))
    {
        return cv::Mat();
    }
    cv::Mat buf(1, bufferlen, CV_8U, (void*)buffer);
    cv::Mat mat =  cv::imdecode(buf, cv::IMREAD_UNCHANGED);
    if (mat.empty())
    {
        printf("fail to load img");
    }
    buf.release();
    return mat;
}

int main()
{
    //读的时候要读取alpha通道
    Mat png_img = imread("test_png4.png",cv::IMREAD_UNCHANGED);
    cout<<png_img.size()<<endl;
    cout<<png_img.channels()<<endl;
    vector<uchar>buffer;
    //将图像编码成字节流
    imencode(".png", png_img, buffer);
//    for(int i =0;i<buffer.size();i++)
//    {
//        cout<<(unsigned char)buffer[i]<<endl;
//    }
    const char * buf = reinterpret_cast<char*>(buffer.data());
    Mat output = loadcvmatfrommem(buf, int(buffer.size()), 1);
    cout<<png_img.channels()<<endl;
}
