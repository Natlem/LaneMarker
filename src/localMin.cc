#include "localMin.hh"


std::pair<double, double> getFunc(cv::Vec4i& c)
{
    // y = ax + b;
    double a = (double)(c[3] - c[1]) / (double)(c[2] - c[0]);
    double b = (double)c[1] - (c[0] * a);
    return std::pair<double,double>(a,b);
}

cv::Point getIntersect(std::pair<double, double>& p, int height)
{
    double x = (height - p.second) / p.first;
    return cv::Point(x,height);
}

cv::Point getIntersect(cv::Vec4i& c, int height)
{
    std::pair<double, double> p = getFunc(c);
    double x = (height - p.second) / p.first;
    return cv::Point(x,height);

}

cv::Point getIntersect(cv::Vec4i& l1, cv::Vec4i& l2)
{
    std::pair<double, double> f1 = getFunc(l1);
    std::pair<double, double> f2 = getFunc(l2);
    
    double x = (f2.second - f1.second) / (f1.first - f2.first);
    double y = x * f1.first + f1.second;
    return cv::Point(static_cast<int>(x),static_cast<int>(y));
}
