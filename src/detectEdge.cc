#include "detectEdge.hh"
#include <iostream>

void sobelDetect(cv::Mat& inputImg, cv::Mat& outputImg)
{
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    GaussianBlur( inputImg, inputImg, cv::Size(3,3), 0, 0);
    //cvtColor( inputImg, inputImg, CV_RGB2GRAY );
    // Gradient X
    Sobel( inputImg, grad_x, ddepth, 1, 0, 3, scale, delta);
    convertScaleAbs( grad_x, abs_grad_x );
    //        /// Gradient Y
    Sobel( inputImg, grad_y, ddepth, 0, 1, 3, scale, delta);
    convertScaleAbs( grad_y, abs_grad_y );
    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, outputImg); 
}

