//core包含的是一些核心的操作，比如Mat等的定义
//imgcodes包含图像载入和写到磁盘等
//highgui包含一些显示相关的操作

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;


int main()
{
    //读取图像
    std::string image_path = "starry_night.jpg";
    Mat img = imread(image_path, IMREAD_COLOR);

    //标准操作，判断是否为空
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    //显示图像
    imshow("Display window", img);
    int k = waitKey(0); // 必须要加，否则显示窗口一闪而过。参数为0代表等待按键响应


    //保存图像
    if(k == 's')
    {
        imwrite("starry_night.png", img);
    }
    if (k=='q' ||k=='Q')
    {
        break;
    }

    return 0;
}
