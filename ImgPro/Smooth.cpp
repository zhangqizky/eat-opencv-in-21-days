#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;


/// 全局变量
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;
//显示窗口名称
char window_name[] = "Smoothing Demo";

/// 函数定义
int display_caption( const char* caption );
int display_dst( int delay );

//各种滤波函数的展示
int main( int argc, char ** argv )
{
    namedWindow( window_name, WINDOW_AUTOSIZE );

    /// 载入图像
    const char* filename = argc >=2 ? argv[1] : "lena.jpg";

    src = imread( samples::findFile( filename ), IMREAD_COLOR );
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
        return EXIT_FAILURE;
    }

    if( display_caption( "Original Image" ) != 0 )
    {
        return 0;
    }

    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
    {
        return 0;
    }

    /// 均值滤波
    if( display_caption( "Homogeneous Blur" ) != 0 )
    {
        return 0;
    }

    //![均值滤波]
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        blur( src, dst, Size( i, i ), Point(-1,-1) );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    //![blur]

    /// 高斯滤波
    if( display_caption( "Gaussian Blur" ) != 0 )
    {
        return 0;
    }

    //![高斯滤波]
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        GaussianBlur( src, dst, Size( i, i ), 0, 0 );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    //![高斯滤波]

    /// Applying Median blur
    if( display_caption( "Median Blur" ) != 0 )
    {
        return 0;
    }

    //![中值滤波]
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        medianBlur ( src, dst, i );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    //![中值滤波]

    /// 双边滤波
    if( display_caption( "Bilateral Blur" ) != 0 )
    {
        return 0;
    }

    //![双边滤波]
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        bilateralFilter ( src, dst, i, i*2, i/2 );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    //![双边滤波]

    /// Done
    display_caption( "Done!" );

    return 0;
}

/**
 * @function display_caption
 */
int display_caption( const char* caption )
{
    dst = Mat::zeros( src.size(), src.type() );
    putText( dst, caption,
             Point( src.cols/4, src.rows/2),
             FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );

    return display_dst(DELAY_CAPTION);
}

/**
 * @function display_dst
 */
int display_dst( int delay )
{
    imshow( window_name, dst );
    int c = waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
}
