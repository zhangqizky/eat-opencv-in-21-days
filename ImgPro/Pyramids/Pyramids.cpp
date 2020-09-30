//
//  Pyramids.cpp
//  LearnOpenCV
//
//  Created by Zhang,Qi on 2020/9/30.
//  Copyright © 2020 Zhang,Qi. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

const char* window_name = "Pyramids Demo";

int main()
{
    /// General instructions
    cout << "\n Zoom In-Out demo \n "
            "------------------  \n"
            " * [i] -> Zoom in   \n"
            " * [o] -> Zoom out  \n"
            " * [ESC] -> Close program \n" << endl;

    //![load]
    
    const char* filename = "";
    
    Mat src = imread( samples::findFile(filename));
    
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default chicky_512.png] \n");
        return EXIT_FAILURE;
    }
    
    for(;;)
    {
        imshow(window_name,src);
        char c = (char)waitKey(0);
        
        if(c == 27)
        {
            break;
        }
        else if(c == 'i')
        {
            pyrUp(src, src,Size(src.cols*2,src.rows*2));
            printf( "** Zoom In: Image x 2 \n" );
        }
        else if (c == 'o')
        {
            pyrDown(src, src,Size(src.cols/2,src.rows/2));
            printf( "** Zoom Out: Image / 2 \n" );
        }
    }
    return EXIT_SUCCESS;
}

