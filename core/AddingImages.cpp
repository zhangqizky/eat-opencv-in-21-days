/**
 * @file AddingImages.cpp
 * @简单的线性混合加法，src1+src2得到dst ( dst = alpha*src1 + beta*src2 )
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

// c++17里面有一个变量beta，为了避免和接下来用的参数混了，所以这里不直接使用std这个域名。
using std::cin;
using std::cout;
using std::endl;

/**
 * @function main
 * @brief Main function
 */
int main( void )
{
   double alpha = 0.5; double beta; double input;

   Mat src1, src2, dst;

   /// 要求用户输入alpha，也就是第一个图像的比例
   cout << " Simple Linear Blender " << endl;
   cout << "-----------------------" << endl;
   cout << "* Enter alpha [0.0-1.0]: ";
   cin >> input;

   // alpha必须在0～1之间
   if( input >= 0 && input <= 1 )
     { alpha = input; }

   //![load]
   /// 读图像，必须是同样的类型和大小
   src1 = imread( samples::findFile("LinuxLogo.jpg") );
   src2 = imread( samples::findFile("WindowsLogo.jpg") );
   //![load]
   
   if( src1.empty() ) { cout << "Error loading src1" << endl; return EXIT_FAILURE; }
   if( src2.empty() ) { cout << "Error loading src2" << endl; return EXIT_FAILURE; }

   //![线性混合图像]
   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 0.0, dst);
   //![线性混合图像]

   //![显示图像]
   imshow( "Linear Blend", dst );
   waitKey(0);
   //![显示图像]

   return 0;
}
