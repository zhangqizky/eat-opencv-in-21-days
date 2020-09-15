#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    //main函数的参数说明，第一个argc代表参数的个数，没有任何参数时为1.argv代表参数，都是char*类型的，如果是其他类型的需要转换一下。
    if( argc != 2)
    {
     cout <<" Usage: " << argv[0] << " ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], IMREAD_COLOR); // 读图像

    if( image.empty() ) // 检查输入是否为空
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // 创造一个窗口，大小是根据图像大小自动的，推荐使用
    imshow( "Display window", image ); // 显示图像

    waitKey(0); //等待按键响应，任意按键退出
    return 0;
}
