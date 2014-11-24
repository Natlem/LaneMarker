#ifndef LOCALMIN_HH
#define LOCALMIN_HH

#include <utility>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

cv::Point getIntersect(std::pair<double, double>& p, int height);
cv::Point getIntersect(cv::Vec4i& l1, cv::Vec4i& l2);
std::pair<double,double> getFunc(cv::Vec4i& c);
cv::Point getIntersect(cv::Vec4i& c, int height);
#endif
