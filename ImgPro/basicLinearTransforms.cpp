

#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;


int main(int argc,char**argv)
{
     CommandLineParser parser( argc, argv, "{@input | lena.jpg | input image}" );
    
    Mat image = imread(samples::findFile(parser.get<String>( "@input" ) ) ));
    
    if(image.empty())
       {
        cout << "Could not open or find the image!\n"<<endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    
    Mat new_image = Mat::zeros( image.size(), image.type());
    
    double alpha = 1.0;
    int beta = 0;
    
    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";    cin >> beta;
    
    //如何自己操作像素来对图像进行线性变换
    for(int y =0;y< image.rows;y++)
    {
        for (int x = 0;x<image.cols;x++)
        {
            for(int c = 0;c<image.channels();c++)
            {
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(alpha*image.at<Vec3b>(y,x)[c] + beta);
            }
        }
    }
    
    imshow("Original Image",Image);
    imshow("New Image",new_image);
    waitKey();
    return 0;
       
}
