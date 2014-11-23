#ifndef THRESHOLD_HH
# define THRESHOLD_HH

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

void thresholding(cv::Mat& input, cv::Mat& output, int threshold = 75);
void thresholding(cv::Mat& input, int threshold = 75);

#endif
