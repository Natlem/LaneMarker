#ifndef CONVERT_HH
#define CONVERT_HH

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//Self implement
void rgb2Ycbcr(cv::Mat& inputImg, cv::Mat& outputImg);

//Using opencv cvtColor
void rgb2Ycbcr2(cv::Mat& inputImg, cv::Mat& outputImg);


void ycbcr2BGR(cv::Mat& inputimg, cv::Mat& outputImg); 
#endif
