#ifndef HOUGH_HH
#define HOUGH_HH

#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "localMin.hh"

std::vector<cv::Vec4i> houghT(cv::Mat& input, cv::Mat& output, int threshold = 100, bool debug = false);

std::vector<cv::Vec4i> getLanesI(std::vector<cv::Vec4i>& lines, int width, int height);
void extendLines(std::vector<cv::Vec4i>& v, int height);
cv::Point lowestPts(cv::Vec4i& c);
void removeHorLine(std::vector<cv::Vec4i>& v);
cv::Point getCenter(cv::Vec4i& c);
std::vector<cv::Vec4i> getLanes(std::vector<cv::Vec4i> lines, int width, int height);
double distance(cv::Point& p1, cv::Point& p2);
#endif
